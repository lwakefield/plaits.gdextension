#include "plaits4.h"

using namespace godot;

Plaits4Stream::Plaits4Stream() {
	patch.note = 60.f;
	patch.harmonics = 0.f;
	patch.timbre = 0.5f;
	patch.morph = 0.5f;
	patch.frequency_modulation_amount = 0.f;
	patch.timbre_modulation_amount = 0.f;
	patch.morph_modulation_amount = 0.f;

	patch.engine = 0;
	patch.decay = 0.5f;
	patch.lpg_colour = 0.5f;

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


	for (int i = 0; i < 4; i++) {
		stmlib::BufferAllocator allocator(buffers[i], sizeof(buffers[i]));
		voices[i].Init(&allocator);
		voice_states[i].note = patch.note;
		voice_states[i].on = false;
	}
}

Plaits4Stream::~Plaits4Stream() { }

void Plaits4Stream::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("set_engine", "x"), &Plaits4Stream::set_engine);
	godot::ClassDB::bind_method(D_METHOD("get_engine"), &Plaits4Stream::get_engine);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "engine", PROPERTY_HINT_ENUM, "virtual_analog_vcf,phase_distortion,six_op1,six_op2,six_op3,wave_terrain,string_machine,chiptune,virtual_analog,waveshaping,fm,grain,additive,wavetable,chord,speech,swarm,noise,particle,string,modal,bass_drum,snare_drum,hi_hat"), "set_engine", "get_engine");

	godot::ClassDB::bind_method(D_METHOD("set_decay", "x"), &Plaits4Stream::set_decay);
	godot::ClassDB::bind_method(D_METHOD("get_decay"), &Plaits4Stream::get_decay);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "decay", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_decay", "get_decay");

	godot::ClassDB::bind_method(D_METHOD("set_lpg_colour", "x"), &Plaits4Stream::set_lpg_colour);
	godot::ClassDB::bind_method(D_METHOD("get_lpg_colour"), &Plaits4Stream::get_lpg_colour);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lpg_colour", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_lpg_colour", "get_lpg_colour");

	godot::ClassDB::bind_method(D_METHOD("set_note", "x"), &Plaits4Stream::set_note);
	godot::ClassDB::bind_method(D_METHOD("get_note"), &Plaits4Stream::get_note);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "note", PROPERTY_HINT_RANGE, "0,127,1.0"), "set_note", "get_note");

	godot::ClassDB::bind_method(D_METHOD("set_harmonics", "x"), &Plaits4Stream::set_harmonics);
	godot::ClassDB::bind_method(D_METHOD("get_harmonics"), &Plaits4Stream::get_harmonics);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "harmonics", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_harmonics", "get_harmonics");

	godot::ClassDB::bind_method(D_METHOD("set_timbre", "x"), &Plaits4Stream::set_timbre);
	godot::ClassDB::bind_method(D_METHOD("get_timbre"), &Plaits4Stream::get_timbre);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "timbre", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_timbre", "get_timbre");

	godot::ClassDB::bind_method(D_METHOD("set_morph", "x"), &Plaits4Stream::set_morph);
	godot::ClassDB::bind_method(D_METHOD("get_morph"), &Plaits4Stream::get_morph);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "morph", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_morph", "get_morph");

	godot::ClassDB::bind_method(D_METHOD("set_level", "x"), &Plaits4Stream::set_level);
	godot::ClassDB::bind_method(D_METHOD("get_level"), &Plaits4Stream::get_level);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "level", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_level", "get_level");

	godot::ClassDB::bind_method(D_METHOD("play_note", "x"), &Plaits4Stream::play_note);
}

double Plaits4Stream::_get_length() const { return 0.f; }

void Plaits4Stream::set_engine(int x) { patch.engine = x; }
int Plaits4Stream::get_engine() { return patch.engine; }

void Plaits4Stream::set_decay(float x) { patch.decay = x; }
float Plaits4Stream::get_decay() { return patch.decay; }

void Plaits4Stream::set_lpg_colour(float x) { patch.lpg_colour = x; }
float Plaits4Stream::get_lpg_colour() { return patch.lpg_colour; }

void Plaits4Stream::set_harmonics(float x) { patch.harmonics = x; }
float Plaits4Stream::get_harmonics() { return patch.harmonics; }

void Plaits4Stream::set_timbre(float x) { patch.timbre = x; }
float Plaits4Stream::get_timbre() { return patch.timbre; }

void Plaits4Stream::set_morph(float x) { patch.morph = x; }
float Plaits4Stream::get_morph() { return patch.morph; }

void Plaits4Stream::set_level(float x) { mods.level = x; }
float Plaits4Stream::get_level() { return mods.level; }

void Plaits4Stream::set_note(float x) { patch.note = x; }
float Plaits4Stream::get_note() { return patch.note; }

void Plaits4Stream::play_note(float x) {
	voice_states[voice_idx].on = true;
	voice_states[voice_idx].note = x;
	voice_idx += 1;
	voice_idx %= active_voices;
}

Ref<AudioStreamPlayback> Plaits4Stream::_instantiate_playback() const {
	Ref<Plaits4StreamPlayback> playback;
	playback.instantiate();
	playback->base = Ref<Plaits4Stream>(this);
	return playback;
}

int Plaits4Stream::render(AudioFrame *p_buffer, float p_rate_scale, int p_frames) {
	plaits::Voice::Frame frames[12];

	for (int i = 0; i < p_frames; i++) {
		p_buffer[i].left = p_buffer[i].right = 0.f;
	}

	for (int i = 0; i < active_voices; i++) {
		mods.trigger = voice_states[i].on ? 1.0 : 0.0;
		patch.note = voice_states[i].note;
		voice_states[i].on = false;

		for (int j = 0; j < p_frames; j += 12) {
			int size = plaits::kBlockSize;
			if (j+size > p_frames) size = p_frames - j;
			voices[i].Render(patch, mods, frames, size);

			for (int k = 0; k < size; k++) {
				p_buffer[j+k].left += CLAMP(frames[k].out / 32767.f, -1.f, 1.f) / 4.f;
				p_buffer[j+k].right += CLAMP(frames[k].out / 32767.f, -1.f, 1.f) / 4.f;
			}
		}
	}

	return p_frames;
}

Plaits4StreamPlayback::Plaits4StreamPlayback() { }

Plaits4StreamPlayback::~Plaits4StreamPlayback() {
	active = false;
}

void Plaits4StreamPlayback::_bind_methods() { }

int Plaits4StreamPlayback::_mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) {
	if (!active) return 0;

	return base->render(p_buffer, p_rate_scale, p_frames);
}

void Plaits4StreamPlayback::_start(double p_from_pos) {
	active = true;
}
void Plaits4StreamPlayback::_stop() {
	active = false;
}
bool Plaits4StreamPlayback::_is_playing() const {
	return active;
}
double Plaits4StreamPlayback::_get_playback_position() const {
	return 0.0;
}
