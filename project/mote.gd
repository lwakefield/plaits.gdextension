extends Sprite2D

@onready var vel = Vector2.RIGHT.rotated(randf() * 2 * PI) * randf_range(200,400)
@onready var plaits = $AudioStreamPlayer2D.stream as PlaitsStream

var note
func _ready() -> void:
	$AudioStreamPlayer2D.play()
	var notes = [0, 2, 4, 6, 9, 11]
	note = 60 + notes[randi_range(0, notes.size()-1)] + 12 * randi_range(-1,1)
	plaits.note = note
	plaits.harmonics = randf_range(0, 1)
	self.scale = Vector2.ZERO

var tickrange = [1000, 10000]
@onready var next_trigger_at = randi_range(tickrange[0], tickrange[1])
func _process(delta: float) -> void:
	position += vel * delta
	position = position.posmodv(get_viewport_rect().size)
	
	plaits.timbre = position.x / get_viewport_rect().size.x
	plaits.morph = position.y / get_viewport_rect().size.y
	
	if Time.get_ticks_msec() > next_trigger_at:
		plaits.play_note(note)
		next_trigger_at = Time.get_ticks_msec() + randi_range(tickrange[0], tickrange[1])
		var t = create_tween()
		t.tween_property(self, "scale", Vector2.ONE, 0)
		t.tween_property(self, "scale", Vector2.ZERO, 1)
