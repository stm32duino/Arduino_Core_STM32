#ifndef __ES_CAMERA_PARSER_H__
#define __ES_CAMERA_PARSER_H__

#include <Arduino.h>
#include "project_configuration.h"

typedef enum {
    CAM_EVENT_NO_EVENT = 0,
    CAM_EVENT_SMOKE = 1,
    CAM_EVENT_FIRE = 2,
} es_frame_event_type_t;

class CameraParser_t
{
  private:
    char camera_read_buffer[CAMERA_READ_BUFFER_SIZE];
    int camera_read_buffer_index = 0;
    bool camera_reading_flag = false;

    // Data for 24-frame
    uint8_t frame_data[NUM_OF_CAM_FRAME];
    bool frame_data_ready[NUM_OF_CAM_FRAME];

  public:
    CameraParser_t(void);
    ~CameraParser_t(void);

    void clear_read_buffer(void);
    void process_char(char c);

    void clear_frame_data_ready_flag(void);
    void set_frame_data_ready_flag(unsigned int frame_number);
    bool get_frame_data_ready_flag(unsigned int frame_number);
    bool is_all_frame_data_ready_flag(void);

    void clear_frame_data(void);
    void set_frame_event(unsigned int frame_number, es_frame_event_type_t event);
    int get_frame_data_u8(uint8_t *data_buffer, int max_len = NUM_OF_CAM_FRAME);
    int get_frame_data_u2(uint8_t *data_buffer, int max_len = (NUM_OF_CAM_FRAME / 4));
};

static CameraParser_t CAMERA_DATA_PARSER;

#endif /* __ES_CAMERA_PARSER_H__ */
