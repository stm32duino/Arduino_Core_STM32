#include "es_camera_parser_v2.h"
#include "es_log.h"
#include "project_configuration.h"

CameraParserV2_t::CameraParserV2_t(void)
{
  clear_frame_data_ready_flag();
  clear_frame_data();
  clear_read_buffer();
}

CameraParserV2_t::~CameraParserV2_t(void)
{
  clear_frame_data_ready_flag();
  clear_frame_data();
  clear_read_buffer();
}

void CameraParserV2_t::clear_read_buffer(void)
{
  memset((void *)camera_read_buffer, 0, CAMERA_READ_BUFFER_SIZE);
  camera_read_buffer_index = 0;
  camera_reading_flag = false;
}

void CameraParserV2_t::process_char(char c)
{
  if (camera_reading_flag == false)
  {
    if ((c == 0xFE) && (camera_read_buffer[camera_read_buffer_index] == 0xFF))
    {
      clear_read_buffer();
      camera_reading_flag = true;
    }

    camera_read_buffer[camera_read_buffer_index] = c; // Add to buffer without increasing camera_read_buffer_index
  }
  else
  {
    camera_read_buffer[camera_read_buffer_index++] = c;
    if ((c == 0x0A) && (camera_read_buffer[camera_read_buffer_index - 2] == 0x0D))
    {
      camera_reading_flag = false;

      int frame_index = 0;
      if (camera_read_buffer_index == 12)
      {
        // Byte 0: Sub-Frame ID
        // Byte 1, 2, 3, 4: Detection Result, float
        // Byte 5, 6, 7, 8, 9: Spare data 0x01, 0x02, 0x03, 0x04, 0x05
        // Byte 10: 0x0D
        // Byte 11: 0x0A
        if ((camera_read_buffer[5] == 0x01) &&
            (camera_read_buffer[6] == 0x02) &&
            (camera_read_buffer[7] == 0x03) &&
            (camera_read_buffer[8] == 0x04) &&
            (camera_read_buffer[9] == 0x05) &&
            (camera_read_buffer[10] == 0x0D) &&
            (camera_read_buffer[11] == 0x0A))
        {
          frame_index = camera_read_buffer[0];

          ParserFloatFormat_t value;
          value.u8.byte0 = camera_read_buffer[1];
          value.u8.byte1 = camera_read_buffer[2];
          value.u8.byte2 = camera_read_buffer[3];
          value.u8.byte3 = camera_read_buffer[4];

          LOG.print("[INFO] CameraParserV2_t::process_char() | Detected data for frame #");
          LOG.print(frame_index);
          LOG.print(", probability = ");
          LOG.println(value.f);

          set_frame_event(frame_index, (value.f >= CAMERA_FIRE_PROBABILITY_THRESHOLD ? CAM_EVENT_FIRE : CAM_EVENT_NO_EVENT), value.f);
        }
        else
        {
          LOG.println("[DEBUG] CameraParserV2_t::process_char() | Wrong format");

          LOG.print("[DEBUG] CameraParserV2_t::process_char() | Read data: ");
          for (int i = 0; i < camera_read_buffer_index; i++)
          {
            LOG.print_hex(camera_read_buffer[i]);
            LOG.print(",");
          }
          LOG.println();
        }
      }
      else
      {
        LOG.print("[DEBUG] CameraParserV2_t::process_char() | Unrecognized buffer length = ");
        LOG.println(camera_read_buffer_index);

        LOG.print("[DEBUG] CameraParserV2_t::process_char() | Read data: ");
        for (int i = 0; i < camera_read_buffer_index; i++)
        {
          LOG.print_hex(camera_read_buffer[i]);
          LOG.print(",");
        }
        LOG.println();
      }
    }
  }
}

void CameraParserV2_t::clear_frame_data_ready_flag(void)
{
  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    frame_data_ready[i] = false;
  }
}

void CameraParserV2_t::set_frame_data_ready_flag(unsigned int frame_number)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return;
  }

  frame_data_ready[frame_number] = true;
}

bool CameraParserV2_t::get_frame_data_ready_flag(unsigned int frame_number)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return false;
  }

  return frame_data_ready[frame_number];
}

bool CameraParserV2_t::is_all_frame_data_ready_flag(void)
{
  bool res = true;
  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    res = res && frame_data_ready[i];
  }

  return res;
}

void CameraParserV2_t::clear_frame_data(void)
{
  clear_frame_data_ready_flag();
  memset((void *)frame_data, 0, NUM_OF_CAM_FRAME); // Equivalent to NoEvent
  memset((void *)frame_probability, 0, NUM_OF_CAM_FRAME * sizeof(float));
}

void CameraParserV2_t::set_frame_event(unsigned int frame_number, es_frame_event_type_t event, float probability)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return;
  }

  set_frame_data_ready_flag(frame_number);
  frame_data[frame_number] = (uint8_t)event;
  frame_probability[frame_number] = probability;
}

int CameraParserV2_t::get_frame_data_u8(uint8_t *data_buffer, int max_len)
{
  if (data_buffer == NULL)
  {
    return -1;
  }

  memcpy(frame_data, data_buffer, (NUM_OF_CAM_FRAME < max_len) ? NUM_OF_CAM_FRAME : max_len);

  if (max_len >= NUM_OF_CAM_FRAME)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int CameraParserV2_t::get_frame_data_u2(uint8_t *data_buffer, int max_len)
{
  if (data_buffer == NULL)
  {
    LOG.println("[ERROR] CameraParserV2_t::get_frame_data_u2() | NULL buffer");
    return -1;
  }

  int dst_byte_index = 0;
  int dst_bit_index = 0;

  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    data_buffer[dst_byte_index] = data_buffer[dst_byte_index] & ~(0b00000011 << dst_bit_index);
    data_buffer[dst_byte_index] |= (frame_data[i] & 0b00000011) << dst_bit_index;

    dst_bit_index += 2;
    if (dst_bit_index >= 8)
    {
      dst_bit_index = 0;
      dst_byte_index++;
      if (dst_byte_index >= max_len)
      {
        return -1;
      }
    }
  }

  return 0;
}

int CameraParserV2_t::get_frame_data_probability_u8(uint8_t *data_buffer, int max_len)
{
  if (data_buffer == NULL)
  {
    return -1;
  }

  int s = (NUM_OF_CAM_FRAME < max_len) ? NUM_OF_CAM_FRAME : max_len;
  for (int i = 0; i < s; i++)
  {
    float temp = (frame_probability[i] * 100.0);
    if (temp < 0)
    {
      temp = 0;
    }
    if (temp > 100)
    {
      temp = 100;
    }

    data_buffer[i] = (uint8_t)temp;
  }

  if (max_len >= NUM_OF_CAM_FRAME)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

bool CameraParserV2_t::is_fire_detected(void)
{
  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    if (frame_probability[i] >= CAMERA_FIRE_PROBABILITY_THRESHOLD)
    {
      return true;
    }
  }

  return false;
}

CameraParserV2_t CAMERA_DATA_PARSER;