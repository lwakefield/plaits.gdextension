#pragma once

#include "godot_cpp/classes/audio_stream_playback.hpp"
#include "godot_cpp/classes/wrapped.hpp"

#include "plaits_stream.h"

using namespace godot;

class PlaitsStreamPlayback : public AudioStreamPlayback {
	GDCLASS(PlaitsStreamPlayback, AudioStreamPlayback)
		friend class PlaitsStream;

	protected:
	static void _bind_methods();
	bool active;
	Ref<PlaitsStream> base;

	public:
	PlaitsStreamPlayback();
	~PlaitsStreamPlayback() override;

	virtual void _start(double p_from_pos = 0.0) override;
	virtual void _stop() override;
	virtual bool _is_playing() const override;
	// virtual int _get_loop_count() const;
	virtual double _get_playback_position() const override;
	// virtual void _seek(double p_time) override;
	virtual int _mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) override;

};
