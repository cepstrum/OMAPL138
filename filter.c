/*
FIR filter designed with
httpt-filter.appspot.com
sampling frequency 44100 Hz
 0 Hz - 6000 Hz
  gain = 1
  desired ripple = 2.5 dB
  actual ripple = 1.798059603701974 dB
 7000 Hz - 7500 Hz
  gain = 1.5
  desired ripple = 1 dB
  actual ripple = 0.6943562689411324 dB
 12000 Hz - 12050 Hz
  gain = 0.65
  desired ripple = 1 dB
  actual ripple = 0.35411470523749733 dB
 15000 Hz - 22050 Hz
  gain = 1.51
  desired ripple = 2 dB
  actual ripple = 1.4211596567155427 dB
*/

#define FILTER_TAP_NUM 17

static double filter_taps[FILTER_TAP_NUM] = {
  -0.0923694208024749,
  -0.03650640543188837,
  0.11875792315420561,
  0.0374948286074147,
  -0.08103564828339961,
  -0.042840979892957355,
  0.06320261016781677,
  -0.13370575066235044,
  1.2308691004305696,
  -0.13370575066235044,
  0.06320261016781677,
  -0.042840979892957355,
  -0.08103564828339961,
  0.0374948286074147,
  0.11875792315420561,
  -0.03650640543188837,
  -0.0923694208024749
};