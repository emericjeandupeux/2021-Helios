#define regaz_width 128
#define regaz_height 64
static unsigned char regaz_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x3f, 0xc0, 0xff, 0x3f, 0xf0, 0x3f, 0x00,
   0x3c, 0x80, 0xff, 0x7f, 0xc0, 0x1f, 0x00, 0x00, 0xf8, 0xff, 0xc0, 0xff,
   0x3f, 0xfc, 0x7f, 0x00, 0x3c, 0x80, 0xff, 0x7f, 0xf0, 0x7f, 0x00, 0x80,
   0xf9, 0xff, 0xc1, 0xff, 0x3f, 0xfc, 0x7f, 0x00, 0xff, 0x80, 0xff, 0x7f,
   0xfc, 0xff, 0x01, 0xc0, 0xf9, 0xff, 0xc7, 0xff, 0x3f, 0xfe, 0xff, 0x81,
   0xff, 0x81, 0xff, 0x7f, 0x7e, 0xe0, 0x07, 0xf0, 0x79, 0xe0, 0xc7, 0x03,
   0x00, 0x3e, 0xf8, 0x81, 0xff, 0x01, 0x00, 0x7c, 0x1e, 0x80, 0x3f, 0xfc,
   0x78, 0xc0, 0xc7, 0x03, 0x00, 0x3e, 0xf0, 0xe1, 0xff, 0x07, 0x00, 0x7e,
   0x06, 0x00, 0xfe, 0x3f, 0x78, 0x80, 0xc7, 0x03, 0x00, 0x1e, 0xe0, 0xe1,
   0xe7, 0x07, 0x00, 0x7f, 0x00, 0x00, 0xf8, 0x1f, 0x78, 0xc0, 0xc7, 0x03,
   0x00, 0x1e, 0x00, 0xf0, 0xe7, 0x0f, 0x80, 0x1f, 0xc0, 0x1f, 0xe0, 0x07,
   0x78, 0xe0, 0xc7, 0x03, 0x00, 0x1e, 0x00, 0xf0, 0x81, 0x0f, 0xc0, 0x0f,
   0xf0, 0x7f, 0x00, 0x80, 0xf9, 0xff, 0xc7, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0x00, 0x0f, 0xe0, 0x0f, 0xf8, 0xff, 0x01, 0xc0, 0xf9, 0xff, 0xc1, 0xff,
   0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf0, 0x03, 0xfc, 0xf0, 0x07, 0xe0,
   0xf9, 0xff, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf8, 0x01,
   0x1e, 0x80, 0x3f, 0xfc, 0xf8, 0x7f, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0xff, 0x0f, 0xfc, 0x01, 0x06, 0x00, 0xfe, 0x3f, 0xf8, 0x1f, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0x1f,
   0x78, 0x3e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x3f, 0x00,
   0x80, 0x0f, 0xe0, 0x07, 0x78, 0x7e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1,
   0xff, 0x8f, 0x3f, 0x00, 0xe0, 0x7f, 0x00, 0x80, 0x79, 0xfc, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0x00, 0x8f, 0x0f, 0x00, 0xf8, 0xff, 0x00, 0xc0,
   0x79, 0xf8, 0xc1, 0x03, 0x00, 0x3e, 0xf8, 0xf1, 0x00, 0x8f, 0x07, 0x00,
   0xfc, 0xf8, 0x03, 0xe0, 0x79, 0xf0, 0xc7, 0xff, 0x3f, 0x3e, 0xf8, 0xf1,
   0x00, 0x8f, 0xff, 0x7f, 0x1e, 0xc0, 0x3f, 0xfc, 0x78, 0xe0, 0xc7, 0xff,
   0x3f, 0xfe, 0xff, 0xf1, 0x00, 0x8f, 0xff, 0x7f, 0x06, 0x00, 0xff, 0x7f,
   0x78, 0xc0, 0xc7, 0xff, 0x3f, 0xfc, 0xff, 0xf0, 0x00, 0x8f, 0xff, 0x7f,
   0x00, 0x00, 0xfc, 0x3f, 0x78, 0x80, 0xc7, 0xff, 0x3f, 0xf0, 0x3f, 0xf0,
   0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xe0, 0x07, 0xf8, 0x07, 0xf8, 0x07,
   0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0xf8, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01,
   0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07,
   0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };
#define regaz1_width 128
#define regaz1_height 64
static unsigned char regaz1_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x3f, 0xc0, 0xff, 0x3f, 0xf0, 0x3f, 0x00,
   0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc0, 0xff,
   0x3f, 0xfc, 0x7f, 0x00, 0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xc1, 0xff, 0x3f, 0xfc, 0x7f, 0x00, 0xff, 0x80, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc7, 0xff, 0x3f, 0xfe, 0xff, 0x81,
   0xff, 0x81, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0xc7, 0x03,
   0x00, 0x3e, 0xf8, 0x81, 0xff, 0x01, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xc0, 0xc7, 0x03, 0x00, 0x3e, 0xf0, 0xe1, 0xff, 0x07, 0x00, 0x7e,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0xc7, 0x03, 0x00, 0x1e, 0xe0, 0xe1,
   0xe7, 0x07, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xc0, 0xc7, 0x03,
   0x00, 0x1e, 0x00, 0xf0, 0xe7, 0x0f, 0x80, 0x1f, 0xc0, 0x1f, 0x00, 0x00,
   0x78, 0xe0, 0xc7, 0x03, 0x00, 0x1e, 0x00, 0xf0, 0x81, 0x0f, 0xc0, 0x0f,
   0xf0, 0x7f, 0x00, 0x80, 0xf9, 0xff, 0xc7, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0x00, 0x0f, 0xe0, 0x0f, 0xf8, 0xff, 0x01, 0xc0, 0xf9, 0xff, 0xc1, 0xff,
   0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf0, 0x03, 0xfc, 0xf0, 0x07, 0xe0,
   0xf9, 0xff, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf8, 0x01,
   0x1e, 0x80, 0x3f, 0xfc, 0xf8, 0x7f, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0xff, 0x0f, 0xfc, 0x01, 0x06, 0x00, 0xfe, 0x3f, 0xf8, 0x1f, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0x1f,
   0x78, 0x3e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x3f, 0x00,
   0x80, 0x0f, 0xe0, 0x07, 0x78, 0x7e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1,
   0xff, 0x8f, 0x3f, 0x00, 0xe0, 0x7f, 0x00, 0x80, 0x79, 0xfc, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0x00, 0x8f, 0x0f, 0x00, 0xf8, 0xff, 0x00, 0xc0,
   0x79, 0xf8, 0xc1, 0x03, 0x00, 0x3e, 0xf8, 0xf1, 0x00, 0x8f, 0x07, 0x00,
   0xfc, 0xf8, 0x03, 0xe0, 0x79, 0xf0, 0xc7, 0xff, 0x3f, 0x3e, 0xf8, 0xf1,
   0x00, 0x8f, 0xff, 0x7f, 0x1e, 0xc0, 0x3f, 0xfc, 0x78, 0xe0, 0xc7, 0xff,
   0x3f, 0xfe, 0xff, 0xf1, 0x00, 0x8f, 0xff, 0x7f, 0x06, 0x00, 0xff, 0x7f,
   0x78, 0xc0, 0xc7, 0xff, 0x3f, 0xfc, 0xff, 0xf0, 0x00, 0x8f, 0xff, 0x7f,
   0x00, 0x00, 0xfc, 0x3f, 0x78, 0x80, 0xc7, 0xff, 0x3f, 0xf0, 0x3f, 0xf0,
   0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xe0, 0x07, 0xf8, 0x07, 0xf8, 0x07,
   0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0xf8, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01,
   0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07,
   0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };
#define regaz2_width 128
#define regaz2_height 64
static unsigned char regaz2_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x3f, 0xc0, 0xff, 0x3f, 0xf0, 0x3f, 0x00,
   0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc0, 0xff,
   0x3f, 0xfc, 0x7f, 0x00, 0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xc1, 0xff, 0x3f, 0xfc, 0x7f, 0x00, 0xff, 0x80, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc7, 0xff, 0x3f, 0xfe, 0xff, 0x81,
   0xff, 0x81, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0xc7, 0x03,
   0x00, 0x3e, 0xf8, 0x81, 0xff, 0x01, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xc0, 0xc7, 0x03, 0x00, 0x3e, 0xf0, 0xe1, 0xff, 0x07, 0x00, 0x7e,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0xc7, 0x03, 0x00, 0x1e, 0xe0, 0xe1,
   0xe7, 0x07, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xc0, 0xc7, 0x03,
   0x00, 0x1e, 0x00, 0xf0, 0xe7, 0x0f, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xe0, 0xc7, 0x03, 0x00, 0x1e, 0x00, 0xf0, 0x81, 0x0f, 0xc0, 0x0f,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc7, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0x00, 0x0f, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc1, 0xff,
   0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf0, 0x03, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf8, 0x01,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0xff, 0x0f, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x78, 0x3e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x3f, 0x00,
   0x80, 0x0f, 0x00, 0x00, 0x78, 0x7e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1,
   0xff, 0x8f, 0x3f, 0x00, 0xe0, 0x7f, 0x00, 0x80, 0x79, 0xfc, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0x00, 0x8f, 0x0f, 0x00, 0xf8, 0xff, 0x00, 0xc0,
   0x79, 0xf8, 0xc1, 0x03, 0x00, 0x3e, 0xf8, 0xf1, 0x00, 0x8f, 0x07, 0x00,
   0xfc, 0xf8, 0x03, 0xe0, 0x79, 0xf0, 0xc7, 0xff, 0x3f, 0x3e, 0xf8, 0xf1,
   0x00, 0x8f, 0xff, 0x7f, 0x1e, 0xc0, 0x3f, 0xfc, 0x78, 0xe0, 0xc7, 0xff,
   0x3f, 0xfe, 0xff, 0xf1, 0x00, 0x8f, 0xff, 0x7f, 0x06, 0x00, 0xff, 0x7f,
   0x78, 0xc0, 0xc7, 0xff, 0x3f, 0xfc, 0xff, 0xf0, 0x00, 0x8f, 0xff, 0x7f,
   0x00, 0x00, 0xfc, 0x3f, 0x78, 0x80, 0xc7, 0xff, 0x3f, 0xf0, 0x3f, 0xf0,
   0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xe0, 0x07, 0xf8, 0x07, 0xf8, 0x07,
   0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0xf8, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01,
   0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07,
   0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };
#define regaz3_width 128
#define regaz3_height 64
static unsigned char regaz3_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x3f, 0xc0, 0xff, 0x3f, 0xf0, 0x3f, 0x00,
   0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc0, 0xff,
   0x3f, 0xfc, 0x7f, 0x00, 0x3c, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xc1, 0xff, 0x3f, 0xfc, 0x7f, 0x00, 0xff, 0x80, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc7, 0xff, 0x3f, 0xfe, 0xff, 0x81,
   0xff, 0x81, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0xc7, 0x03,
   0x00, 0x3e, 0xf8, 0x81, 0xff, 0x01, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xc0, 0xc7, 0x03, 0x00, 0x3e, 0xf0, 0xe1, 0xff, 0x07, 0x00, 0x7e,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0xc7, 0x03, 0x00, 0x1e, 0xe0, 0xe1,
   0xe7, 0x07, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xc0, 0xc7, 0x03,
   0x00, 0x1e, 0x00, 0xf0, 0xe7, 0x0f, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xe0, 0xc7, 0x03, 0x00, 0x1e, 0x00, 0xf0, 0x81, 0x0f, 0xc0, 0x0f,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc7, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0x00, 0x0f, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xc1, 0xff,
   0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf0, 0x03, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1, 0x00, 0x0f, 0xf8, 0x01,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f, 0xc0, 0xff, 0x07, 0x1e, 0xff, 0xf1,
   0xff, 0x0f, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x78, 0x3e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1, 0xff, 0x0f, 0x3f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x7e, 0xc0, 0x03, 0x00, 0x1e, 0xe0, 0xf1,
   0xff, 0x8f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xc0, 0x03,
   0x00, 0x1e, 0xe0, 0xf1, 0x00, 0x8f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xf8, 0xc1, 0x03, 0x00, 0x3e, 0xf8, 0xf1, 0x00, 0x8f, 0x07, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x78, 0xf0, 0xc7, 0xff, 0x3f, 0x3e, 0xf8, 0xf1,
   0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0xc7, 0xff,
   0x3f, 0xfe, 0xff, 0xf1, 0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0x78, 0xc0, 0xc7, 0xff, 0x3f, 0xfc, 0xff, 0xf0, 0x00, 0x8f, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0xc7, 0xff, 0x3f, 0xf0, 0x3f, 0xf0,
   0x00, 0x8f, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xe0, 0x07, 0xf8, 0x07, 0xf8, 0x07,
   0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0xf8, 0x07, 0xf8, 0x07, 0xf8, 0x1f, 0xe0, 0x07, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01, 0xf8, 0x07, 0x18, 0x18,
   0xf8, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x80, 0x01,
   0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18, 0x98, 0x01, 0x18, 0x18,
   0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x60, 0x06, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x06, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07,
   0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18, 0xf8, 0x07, 0xe0, 0x07,
   0x18, 0x18, 0xf8, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0xe0, 0x07, 0x18, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

