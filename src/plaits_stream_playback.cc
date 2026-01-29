#include "plaits_stream_playback.h"

PlaitsStreamPlayback::PlaitsStreamPlayback() { }

PlaitsStreamPlayback::~PlaitsStreamPlayback() {
	active = false;
}

void PlaitsStreamPlayback::_bind_methods() { }

int PlaitsStreamPlayback::_mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) {
	// TEST TONE
	// int mix_rate = 44100;
	// float hz = 440;
	// for (int i = 0; i < p_frames; i++) {
	// 	float inc = 1.0 / (float(mix_rate) / hz);
	// 	pos += inc;
	// 	if (pos > 1.0) {
	// 		pos -= 1.0;
	// 	}
	// 	p_buffer[i].left = sin(2.0 * Math_PI * pos);
	// 	p_buffer[i].right = sin(2.0 * Math_PI * pos);
	// }
	// return p_frames;

	if (!active) return 0;

	return base->render(p_buffer, p_rate_scale, p_frames);
}

void PlaitsStreamPlayback::_start(double p_from_pos) {
	active = true;
}
void PlaitsStreamPlayback::_stop() {
	active = false;
}
bool PlaitsStreamPlayback::_is_playing() const {
	return active;
}
double PlaitsStreamPlayback::_get_playback_position() const {
	return 0.0;
}
