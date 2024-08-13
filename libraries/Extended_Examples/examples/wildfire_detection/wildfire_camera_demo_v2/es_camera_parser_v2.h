#ifndef __ES_CAMERA_PARSER_V2_H__
#define __ES_CAMERA_PARSER_V2_H__

#include <Arduino.h>
#include "project_configuration.h"

typedef enum {
    CAM_EVENT_NO_EVENT = 0,
    CAM_EVENT_SMOKE = 1,
    CAM_EVENT_FIRE = 2,
} es_frame_event_type_t;

#define REVERSE_BYTE_ORDER 0
typedef union {
	float f;
	uint32_t u32;
	struct {
#if (REVERSE_BYTE_ORDER == 0)
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
#else
		uint8_t byte3;
		uint8_t byte2;
		uint8_t byte1;
		uint8_t byte0;
#endif /* REVERSE_BYTE_ORDER */
	} u8;
} ParserFloatFormat_t;

class CameraParserV2_t
{
  private:
    char camera_read_buffer[CAMERA_READ_BUFFER_SIZE];
    int camera_read_buffer_index = 0;
    bool camera_reading_flag = false;

    // Data for 24-frame
    uint8_t frame_data[NUM_OF_CAM_FRAME];
    float frame_probability[NUM_OF_CAM_FRAME];
    bool frame_data_ready[NUM_OF_CAM_FRAME];

  public:
    CameraParserV2_t(void);
    ~CameraParserV2_t(void);

    void clear_read_buffer(void);
    void process_char(char c);

    void clear_frame_data_ready_flag(void);
    void set_frame_data_ready_flag(unsigned int frame_number);
    bool get_frame_data_ready_flag(unsigned int frame_number);
    bool is_all_frame_data_ready_flag(void);

    void clear_frame_data(void);
    void set_frame_event(unsigned int frame_number, es_frame_event_type_t event, float probability);
    int get_frame_data_u8(uint8_t *data_buffer, int max_len = NUM_OF_CAM_FRAME);
    int get_frame_data_u2(uint8_t *data_buffer, int max_len = (NUM_OF_CAM_FRAME / 4));
    int get_frame_data_probability_u8(uint8_t *data_buffer, int max_len = NUM_OF_CAM_FRAME);
    bool is_fire_detected(void);
};

extern CameraParserV2_t CAMERA_DATA_PARSER;

#endif /* __ES_CAMERA_PARSER_V2_H__ */
