#pragma once

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class CellularAutomata : public RefCounted {
	GDCLASS(CellularAutomata, RefCounted);

	RandomNumberGenerator *rng;

	int adjacent_walls_threshold = 5;
	int nearby_walls_threshold = 2;

	void random_fill(Vector<bool> &p_map, int p_width, int p_height, int p_density) const;
	Vector<bool> step(const Vector<bool> &p_map, int p_width, int p_height) const;

	bool get_tile_type(const Vector<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const;

	int get_adjacent_walls_count(const Vector<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const;
	int get_nearby_walls_count(const Vector<bool> &p_map, int p_width, int p_height, int p_x, int p_y) const;

protected:
	static void _bind_methods();

public:
	TypedArray<bool> generate(int p_width, int p_height, int p_iterations, int p_density, int p_seed = 0) const;

	void set_adjacent_walls_threshold(int p_threshold);
	int get_adjacent_walls_threshold() const { return adjacent_walls_threshold; }

	void set_nearby_walls_threshold(int p_threshold);
	int get_nearby_walls_threshold() const { return nearby_walls_threshold; }

	CellularAutomata();
	~CellularAutomata();
};
