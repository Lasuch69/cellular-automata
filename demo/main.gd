extends Node2D

const WIDTH: int = 256
const HEIGHT: int = 256

const ITERATIONS: int = 5
const DENSITY: int = 45

var cellular_automata := CellularAutomata.new()

func _ready() -> void:
#	cellular_automata.adjacent_walls_threshold = 6
#	cellular_automata.nearby_walls_threshold = 1
	
	var map: Array[bool] = cellular_automata.generate(WIDTH, HEIGHT, ITERATIONS, DENSITY)
	
	var buffer: PackedByteArray = map.map(func(value: bool): return int(value) * 255)
	
	var image: Image = Image.create_from_data(WIDTH, HEIGHT, false, Image.FORMAT_L8, buffer)
	var texture: ImageTexture = ImageTexture.create_from_image(image)
	
	$Sprite2D.texture = texture
