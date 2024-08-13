#include "es_camera_parser.h"
#include "project_configuration.h"

CameraParser_t::CameraParser_t(void)
{
  clear_frame_data_ready_flag();
  clear_frame_data();
  clear_read_buffer();
}

CameraParser_t::~CameraParser_t(void)
{
  clear_frame_data_ready_flag();
  clear_frame_data();
  clear_read_buffer();
}

void CameraParser_t::clear_read_buffer(void)
{
  memset((void *)camera_read_buffer, 0, CAMERA_READ_BUFFER_SIZE);
  camera_read_buffer_index = 0;
  camera_reading_flag = false;
}

void CameraParser_t::process_char(char c)
{
  // Process buffer
  if (c == 'i') // Line start character
  {
    camera_reading_flag = true;
  }

  if (camera_reading_flag == true)
  {
    camera_read_buffer[camera_read_buffer_index++] = c;
  }

  if (c == '\n') // Line stop character
  {
    camera_reading_flag = false;
    int frame_index = 0;
    char event_first_char = '\0';

    if ((13 <= camera_read_buffer_index) && (camera_read_buffer_index <= 17))
    {
      if ((sscanf(camera_read_buffer, "img %d : %cire", &frame_index, &event_first_char) == 2) && (event_first_char == 'F'))
      {
        // Todo: Error return & logging
        // USB_SERIAL.print("[INFO] Fire detection in frame: ");
        // USB_SERIAL.println(frame_index);
        set_frame_event(frame_index, CAM_EVENT_FIRE);
      }
      else
      {
        // Todo: Error return & logging
        // USB_SERIAL.println("[ERROR] Error parsing in Fire detection");
      }

      if ((sscanf(camera_read_buffer, "img %d : %cmoke", &frame_index, &event_first_char) == 2) && (event_first_char == 'S'))
      {
        // Todo: Error return & logging
        // USB_SERIAL.print("[INFO] Smoke detection in frame: ");
        // USB_SERIAL.println(frame_index);
        set_frame_event(frame_index, CAM_EVENT_SMOKE);
      }
      else
      {
        // Todo: Error return & logging
        // USB_SERIAL.println("[ERROR] Error parsing in Smoke detection");
      }

      if ((sscanf(camera_read_buffer, "img %d : %coEvent", &frame_index, &event_first_char) == 2) && (event_first_char == 'N'))
      {
        // Todo: Error return & logging
        // USB_SERIAL.print("[INFO] NoEvent detection in frame: ");
        // USB_SERIAL.println(frame_index);
        set_frame_event(frame_index, CAM_EVENT_NO_EVENT);
      }
      else
      {
        // Todo: Error return & logging
        // USB_SERIAL.println("[ERROR] Error parsing in NoEvent detection");
      }
    }
    else
    {
      // Todo: Error return & logging
      // USB_SERIAL.print("[ERROR] Wrong input buffer lenght: ");
      // USB_SERIAL.println(camera_read_buffer_index);
    }

    clear_read_buffer();
  }
  // Validate buffer size
  if (camera_read_buffer_index >= CAMERA_READ_BUFFER_SIZE)
  {
    clear_read_buffer();
  }
}

void CameraParser_t::clear_frame_data_ready_flag(void)
{
  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    frame_data_ready[i] = false;
  }
}

void CameraParser_t::set_frame_data_ready_flag(unsigned int frame_number)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return;
  }

  frame_data_ready[frame_number] = true;
}

bool CameraParser_t::get_frame_data_ready_flag(unsigned int frame_number)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return false;
  }

  return frame_data_ready[frame_number];
}

bool CameraParser_t::is_all_frame_data_ready_flag(void)
{
    bool res = true;
    for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
    {
        res = res && frame_data_ready[i];
    }

    return res;
}

void CameraParser_t::clear_frame_data(void)
{
  clear_frame_data_ready_flag();
  memset((void *)frame_data, 0, NUM_OF_CAM_FRAME); // Equivalent to NoEvent
}

void CameraParser_t::set_frame_event(unsigned int frame_number, es_frame_event_type_t event)
{
  if (frame_number >= NUM_OF_CAM_FRAME)
  {
    return;
  }

  set_frame_data_ready_flag(frame_number);
  frame_data[frame_number] = (uint8_t)event;
}

int CameraParser_t::get_frame_data_u8(uint8_t *data_buffer, int max_len)
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

int CameraParser_t::get_frame_data_u2(uint8_t *data_buffer, int max_len)
{
  if (data_buffer == NULL)
  {
    return -1;
  }

  int dst_byte_index = 0;
  int dst_bit_index = 0;

  for (int i = 0; i < NUM_OF_CAM_FRAME; i++)
  {
    data_buffer[dst_byte_index] = data_buffer[dst_byte_index] & (~0b00000011 << dst_bit_index);
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
