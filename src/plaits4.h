#pragma once

#include <godot_cpp/classes/audio_frame.hpp>
#include "godot_cpp/classes/audio_stream.hpp"
#include "godot_cpp/classes/audio_stream_playback.hpp"
#include "godot_cpp/classes/audio_server.hpp"
#include "godot_cpp/classes/wrapped.hpp"

#include "plaits/dsp/voice.h"


using namespace godot;

struct VoiceState {
	bool on;
	float note;
};

class Plaits4Stream : public AudioStream {
	GDCLASS(Plaits4Stream, AudioStream)

	protected:
		static void _bind_methods();
		plaits::Voice voice;
		plaits::Patch patch;
		plaits::Modulations mods;
		char buffers[4][16384];

		plaits::Voice voices[4];
		VoiceState voice_states[4];
		int voice_idx = 0;
		int active_voices = 4;

	public:
		Plaits4Stream();
		~Plaits4Stream() override;
		virtual Ref<AudioStreamPlayback> _instantiate_playback() const override;
		virtual double _get_length() const override;
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

class Plaits4StreamPlayback : public AudioStreamPlayback {
	GDCLASS(Plaits4StreamPlayback, AudioStreamPlayback)
		friend class Plaits4Stream;

	protected:
	static void _bind_methods();
	bool active;
	Ref<Plaits4Stream> base;

	public:
	Plaits4StreamPlayback();
	~Plaits4StreamPlayback() override;

	virtual void _start(double p_from_pos = 0.0) override;
	virtual void _stop() override;
	virtual bool _is_playing() const override;
	// virtual int _get_loop_count() const;
	virtual double _get_playback_position() const override;
	// virtual void _seek(double p_time) override;
	virtual int _mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) override;

};
