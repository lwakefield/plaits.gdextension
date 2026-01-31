#pragma once

#include <godot_cpp/classes/audio_frame.hpp>
#include "godot_cpp/classes/audio_stream.hpp"
#include "godot_cpp/classes/audio_server.hpp"
#include "godot_cpp/classes/wrapped.hpp"

#include "plaits/dsp/voice.h"


using namespace godot;

class PlaitsStream : public AudioStream {
	GDCLASS(PlaitsStream, AudioStream)

	protected:
		static void _bind_methods();
		plaits::Voice voice;
		plaits::Patch patch;
		plaits::Modulations mods;
		char buffer[16384];
		bool trigger_note = false;
		int play_mode = 0;

	public:
		PlaitsStream();
		~PlaitsStream() override;
		virtual Ref<AudioStreamPlayback> _instantiate_playback() const override;
		virtual double _get_length() const override;
		int test();
		int render(AudioFrame *p_buffer, float p_rate_scale, int p_frames);
		void set_engine(int x);
		int get_engine();

		void set_decay(float x);
		float get_decay();

		void set_lpg_colour(float x);
		float get_lpg_colour();

		void set_note(float x);
		float get_note();

		void set_harmonics(float x);
		float get_harmonics();

		void set_timbre(float x);
		float get_timbre();

		void set_morph(float x);
		float get_morph();

		void set_level(float x);
		float get_level();

		void set_play_mode(int x);
		int get_play_mode();

		void play_note(float x);
};
