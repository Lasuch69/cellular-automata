extends Node2D

const WIDTH: int = 256
const HEIGHT: int = 256

const ITERATIONS: int = 5
const DENSITY: int = 45

var cellular_automata := CellularAutomata.new()

func redraw(p_seed: int = 0) -> void:
	var map: Array[bool] = cellular_automata.generate(WIDTH, HEIGHT, ITERATIONS, DENSITY, p_seed)
	
	var buffer: PackedByteArray = map.map(func(value: bool): return int(value) * 255)
	
	var image: Image = Image.create_from_data(WIDTH, HEIGHT, false, Image.FORMAT_L8, buffer)
	var texture: ImageTexture = ImageTexture.create_from_image(image)
	
	$Sprite2D.texture = texture

func _input(event: InputEvent) -> void:
	if event.is_action("ui_accept") and event.is_pressed():
		redraw(randi())
