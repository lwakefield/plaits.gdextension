extends Node2D

var mote = load("res://mote.tscn")

func _ready() -> void:
	for i in range(10):
		var m = mote.instantiate()
		m.tickrange = [1000, 10000]
		add_child(m)
