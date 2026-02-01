#include "plaits_stream.h"
#include "plaits_stream_playback.h"

PlaitsStream::PlaitsStream() {
	patch.decay = 0.5f;
	patch.engine = 0;
	patch.note = 60.f;
	patch.harmonics = 0.f;
	patch.timbre = 0.5f;
	patch.morph = 0.5f;

	patch.lpg_colour = 0.5f;
	patch.timbre_modulation_amount = 0.f;
	patch.morph_modulation_amount = 0.f;
	patch.frequency_modulation_amount = 0.f;

	mods.engine = 0.f;
	mods.note = 0.f;
	mods.frequency = 0.f;
	mods.harmonics = 0.f;
	mods.timbre = 0.f;
	mods.morph = 0.f;
	mods.trigger = 0.f;
	mods.level = 1.f;

	mods.frequency_patched = false;
	mods.timbre_patched = false;
	mods.morph_patched = false;
	mods.trigger_patched = true;
	mods.level_patched = false;

	stmlib::BufferAllocator allocator(buffer, sizeof(buffer));
	voice.Init(&allocator);
}

PlaitsStream::~PlaitsStream() { }

void PlaitsStream::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("set_engine", "x"), &PlaitsStream::set_engine);
	godot::ClassDB::bind_method(D_METHOD("get_engine"), &PlaitsStream::get_engine);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "engine", PROPERTY_HINT_ENUM, "virtual_analog_vcf,phase_distortion,six_op1,six_op2,six_op3,wave_terrain,string_machine,chiptune,virtual_analog,waveshaping,fm,grain,additive,wavetable,chord,speech,swarm,noise,particle,string,modal,bass_drum,snare_drum,hi_hat"), "set_engine", "get_engine");

	godot::ClassDB::bind_method(D_METHOD("set_decay", "x"), &PlaitsStream::set_decay);
	godot::ClassDB::bind_method(D_METHOD("get_decay"), &PlaitsStream::get_decay);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "decay", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_decay", "get_decay");

	godot::ClassDB::bind_method(D_METHOD("set_lpg_colour", "x"), &PlaitsStream::set_lpg_colour);
	godot::ClassDB::bind_method(D_METHOD("get_lpg_colour"), &PlaitsStream::get_lpg_colour);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lpg_colour", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_lpg_colour", "get_lpg_colour");

	godot::ClassDB::bind_method(D_METHOD("set_note", "x"), &PlaitsStream::set_note);
	godot::ClassDB::bind_method(D_METHOD("get_note"), &PlaitsStream::get_note);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "note", PROPERTY_HINT_RANGE, "0,127,1.0"), "set_note", "get_note");

	godot::ClassDB::bind_method(D_METHOD("set_harmonics", "x"), &PlaitsStream::set_harmonics);
	godot::ClassDB::bind_method(D_METHOD("get_harmonics"), &PlaitsStream::get_harmonics);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "harmonics", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_harmonics", "get_harmonics");

	godot::ClassDB::bind_method(D_METHOD("set_timbre", "x"), &PlaitsStream::set_timbre);
	godot::ClassDB::bind_method(D_METHOD("get_timbre"), &PlaitsStream::get_timbre);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "timbre", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_timbre", "get_timbre");

	godot::ClassDB::bind_method(D_METHOD("set_morph", "x"), &PlaitsStream::set_morph);
	godot::ClassDB::bind_method(D_METHOD("get_morph"), &PlaitsStream::get_morph);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "morph", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_morph", "get_morph");

	godot::ClassDB::bind_method(D_METHOD("set_play_mode", "x"), &PlaitsStream::set_play_mode);
	godot::ClassDB::bind_method(D_METHOD("get_play_mode"), &PlaitsStream::get_play_mode);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "play_mode", PROPERTY_HINT_ENUM, "Drone,Triggered"), "set_play_mode", "get_play_mode");

	godot::ClassDB::bind_method(D_METHOD("set_level", "x"), &PlaitsStream::set_level);
	godot::ClassDB::bind_method(D_METHOD("get_level"), &PlaitsStream::get_level);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "level", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_level", "get_level");

	godot::ClassDB::bind_method(D_METHOD("play_note", "x"), &PlaitsStream::play_note);
}

Ref<AudioStreamPlayback> PlaitsStream::_instantiate_playback() const {
	Ref<PlaitsStreamPlayback> playback;
	playback.instantiate();
	playback->base = Ref<PlaitsStream>(this);
	return playback;
}

double PlaitsStream::_get_length() const {
	return 0.f;
}

void PlaitsStream::set_engine(int x) { patch.engine = x; }
int PlaitsStream::get_engine() { return patch.engine; }

void PlaitsStream::set_decay(float x) { patch.decay = x; }
float PlaitsStream::get_decay() { return patch.decay; }

void PlaitsStream::set_lpg_colour(float x) { patch.lpg_colour = x; }
float PlaitsStream::get_lpg_colour() { return patch.lpg_colour; }

void PlaitsStream::set_harmonics(float x) { patch.harmonics = x; }
float PlaitsStream::get_harmonics() { return patch.harmonics; }

void PlaitsStream::set_timbre(float x) { patch.timbre = x; }
float PlaitsStream::get_timbre() { return patch.timbre; }

void PlaitsStream::set_morph(float x) { patch.morph = x; }
float PlaitsStream::get_morph() { return patch.morph; }

void PlaitsStream::set_level(float x) { mods.level = x; }
float PlaitsStream::get_level() { return mods.level; }

void PlaitsStream::set_note(float x) { patch.note = x; }
float PlaitsStream::get_note() { return patch.note; }

void PlaitsStream::set_play_mode(int x) { play_mode = x; }
int PlaitsStream::get_play_mode() { return play_mode; }

void PlaitsStream::play_note(float x) {
	patch.note = x;
	trigger_note = true;
}

int PlaitsStream::render(AudioFrame *p_buffer, float p_rate_scale, int p_frames) {
	float target_rate = AudioServer::get_singleton()->get_mix_rate();

	// Plaits assumes a 48kHz sample rate, but ours is probably different.
	// float ratio = 48000.f / target_rate;
	// for some reason, we are getting the correct freq output now, despite
	// the fact that we are operating at a different sample speed? I am
	// probably missing something...

	mods.trigger_patched = play_mode == 1;
	mods.level_patched = play_mode == 0;
	if (trigger_note) {
		mods.trigger = 1.0;
		trigger_note = false;
	} else {
		mods.trigger = 0.0;
	}

	plaits::Voice::Frame frames[12];
	for (int i = 0; i < p_frames; i += 12) {

		int size = plaits::kBlockSize;
		if (i+size > p_frames) size = p_frames - i;
		voice.Render(patch, mods, frames, size);

		for (int j = 0; j < size; j++) {
			p_buffer[i+j].left = CLAMP(frames[j].out / 32767.f, -1.f, 1.f);
			p_buffer[i+j].right = CLAMP(frames[j].out / 32767.f, -1.f, 1.f);
		}
	}
	return p_frames;
}
