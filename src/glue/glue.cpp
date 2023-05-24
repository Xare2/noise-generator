
#include <emscripten.h>

EM_JS_DEPS(webidl_binder, "$intArrayFromString");

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.

EM_JS(void, array_bounds_check_error, (size_t idx, size_t size), {
  throw 'Array index ' + idx + ' out of bounds: [0,' + size + ')';
});

void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    array_bounds_check_error(array_idx, array_size);
  }
}

// noise_generator

noise_generator* EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_noise_generator_2(int s, bool color) {
  return new noise_generator(s, color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_set_color_1(noise_generator* self, bool color) {
  self->set_color(color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_set_seed_1(noise_generator* self, int seed) {
  self->set_seed(seed);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_eval_2(noise_generator* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator___destroy___0(noise_generator* self) {
  delete self;
}

// lattice_noise

lattice_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_lattice_noise_4(int noise_grid_resolution, int seed, float frequency, bool color) {
  return new lattice_noise(noise_grid_resolution, seed, frequency, color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_frequency_1(lattice_noise* self, float frequency) {
  self->set_frequency(frequency);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_seed_1(lattice_noise* self, int seed) {
  self->set_seed(seed);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_color_1(lattice_noise* self, bool color) {
  self->set_color(color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_eval_2(lattice_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise___destroy___0(lattice_noise* self) {
  delete self;
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// vector2

float EMSCRIPTEN_KEEPALIVE emscripten_bind_vector2_get_x_0(vector2* self) {
  return self->x;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_vector2_set_x_1(vector2* self, float arg0) {
  self->x = arg0;
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_vector2_get_y_0(vector2* self) {
  return self->y;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_vector2_set_y_1(vector2* self, float arg0) {
  self->y = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_vector2___destroy___0(vector2* self) {
  delete self;
}

// perlin_noise

perlin_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_perlin_noise_4(float frequency, int noise_grid_resolution, int seed, bool color) {
  return new perlin_noise(frequency, noise_grid_resolution, seed, color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_seed_1(perlin_noise* self, int seed) {
  self->set_seed(seed);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_eval_2(perlin_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_frequency_1(perlin_noise* self, float frequency) {
  self->set_frequency(frequency);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_color_1(perlin_noise* self, bool color) {
  self->set_color(color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise___destroy___0(perlin_noise* self) {
  delete self;
}

// value_noise

value_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_value_noise_4(float frequency, int noise_grid_resolution, int seed, bool color) {
  return new value_noise(frequency, noise_grid_resolution, seed, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_eval_2(value_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_frequency_1(value_noise* self, float frequency) {
  self->set_frequency(frequency);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_color_1(value_noise* self, bool color) {
  self->set_color(color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise___destroy___0(value_noise* self) {
  delete self;
}

// white_noise

float EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_eval_2(white_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_frequency_1(white_noise* self, float frequency) {
  self->set_frequency(frequency);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_color_1(white_noise* self, bool color) {
  self->set_color(color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise___destroy___0(white_noise* self) {
  delete self;
}

// voronoi_noise

voronoi_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_voronoi_noise_4(int image_resolution, int cell_amount, int seed, bool color) {
  return new voronoi_noise(image_resolution, cell_amount, seed, color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_cell_amount_1(voronoi_noise* self, int cell_amount) {
  self->set_cell_amount(cell_amount);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_seed_1(voronoi_noise* self, int seed) {
  self->set_seed(seed);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_eval_2(voronoi_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_color_1(voronoi_noise* self, bool color) {
  self->set_color(color);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise___destroy___0(voronoi_noise* self) {
  delete self;
}

}

