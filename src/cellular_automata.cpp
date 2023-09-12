#include "cellular_automata.hpp"
#include "godot_cpp/core/error_macros.hpp"

using namespace godot;

TypedArray<bool> CellularAutomata::generate(int p_width, int p_height, int p_iterations, int p_density) const {
	TypedArray<bool> map;
	map.resize(p_width * p_height);

	random_fill(map, p_width, p_height, p_density);

	for (int i = 0; i < p_iterations; i++) {
		map = step(map, p_width, p_height);
	}

	return map;
}

void CellularAutomata::random_fill(TypedArray<bool> &p_map, int p_width, int p_height, int p_density) const {
	RandomNumberGenerator rng;

	int random_column = rng.randi_range(4, p_width - 4);

	for (int y = 0; y < p_height; y++) {
		for (int x = 0; x < p_width; x++) {
			if (x == 0 || y == 0 || x == p_width - 1 || y == p_height - 1)
				p_map[x + y * p_width] = true;
			else if (x != random_column && rng.randf() * 100 < p_density)
				p_map[x + y * p_width] = true;
		}
	}
}

TypedArray<bool> CellularAutomata::step(const TypedArray<bool> &p_map, int p_width, int p_height) const {
	TypedArray<bool> new_map;
	new_map.resize(p_map.size());

	for (int y = 0; y < p_height; y++) {
		for (int x = 0; x < p_width; x++) {
			if (x == 0 || y == 0 || x == p_width - 1 || y == p_height - 1)
				new_map[x + y * p_width] = true;
			else
				new_map[x + y * p_width] = get_tile_type(p_map, p_width, p_height, x, y);
		}
	}

	return new_map;
}

bool CellularAutomata::get_tile_type(const TypedArray<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const {
	int adjacent_walls = get_adjacent_walls_count(p_map, p_width, p_width, p_x, p_y);
	int nearby_walls = get_nearby_walls_count(p_map, p_width, p_width, p_x, p_y);

	return adjacent_walls >= adjacent_walls_threshold || nearby_walls <= nearby_walls_threshold;
}

int CellularAutomata::get_adjacent_walls_count(const TypedArray<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const {
	int count = 0;

	for (int x = p_x - 1; x <= p_x + 1; x++) {
		for (int y = p_y - 1; y <= p_y + 1; y++) {
			if (p_map[x + y * p_width])
				count++;
		}
	}

	return count;
}

int CellularAutomata::get_nearby_walls_count(const TypedArray<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const {
	int count = 0;

	for (int x = p_x - 2; x <= p_x + 2; x++) {
		for (int y = p_y - 2; y <= p_y + 2; y++) {
			if (Math::abs(x - p_x) == 2 && Math::abs(y - p_y) == 2)
				continue;

			if (x < 0 || y < 0 || x >= p_width || y >= p_height)
				continue;

			if (p_map[x + y * p_width])
				count++;
		}
	}

	return count;
}

void CellularAutomata::set_adjacent_walls_threshold(int p_threshold) {
	adjacent_walls_threshold = p_threshold;
}

void CellularAutomata::set_nearby_walls_threshold(int p_threshold) {
	nearby_walls_threshold = p_threshold;
}

void CellularAutomata::_bind_methods() {
	ClassDB::bind_method(D_METHOD("generate", "width", "height", "iterations", "density"), &CellularAutomata::generate);

	ClassDB::bind_method(D_METHOD("set_adjacent_walls_threshold", "threshold"), &CellularAutomata::set_adjacent_walls_threshold);
	ClassDB::bind_method(D_METHOD("get_adjacent_walls_threshold"), &CellularAutomata::get_adjacent_walls_threshold);

	ClassDB::bind_method(D_METHOD("set_nearby_walls_threshold", "threshold"), &CellularAutomata::set_nearby_walls_threshold);
	ClassDB::bind_method(D_METHOD("get_nearby_walls_threshold"), &CellularAutomata::get_nearby_walls_threshold);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "adjacent_walls_threshold"), "set_adjacent_walls_threshold", "get_adjacent_walls_threshold");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "nearby_walls_threshold"), "set_nearby_walls_threshold", "get_nearby_walls_threshold");
}
