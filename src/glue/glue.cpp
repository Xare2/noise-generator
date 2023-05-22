
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

float EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_rand_01_0(noise_generator* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_get_array_index_3(noise_generator* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

noise_generator* EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_noise_generator_2(int s, bool color) {
  return new noise_generator(s, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_eval_2(noise_generator* self, float x, float y) {
  return self->eval(x, y);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_getImageArray_2(noise_generator* self, int width, int height) {
  return self->getImageArray(width, height);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_get_m_seed_0(noise_generator* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_set_m_seed_1(noise_generator* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_get_m_color_0(noise_generator* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator_set_m_color_1(noise_generator* self, bool arg0) {
  self->m_color = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_noise_generator___destroy___0(noise_generator* self) {
  delete self;
}

// lattice_noise

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_calculate_noise_grid_0(lattice_noise* self) {
  self->calculate_noise_grid();
}

lattice_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_lattice_noise_3(int noise_grid_resolution, int seed, bool color) {
  return new lattice_noise(noise_grid_resolution, seed, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_rand_01_0(lattice_noise* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_get_array_index_3(lattice_noise* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_eval_2(lattice_noise* self, float x, float y) {
  return self->eval(x, y);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_getImageArray_2(lattice_noise* self, int width, int height) {
  return self->getImageArray(width, height);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_get_m_noise_grid_1(lattice_noise* self, int arg0) {
  return self->m_noise_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_m_noise_grid_2(lattice_noise* self, int arg0, float arg1) {
  self->m_noise_grid[arg0] = arg1;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_get_m_noise_grid_resolution_0(lattice_noise* self) {
  return self->m_noise_grid_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_m_noise_grid_resolution_1(lattice_noise* self, int arg0) {
  self->m_noise_grid_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_get_m_seed_0(lattice_noise* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_m_seed_1(lattice_noise* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_get_m_color_0(lattice_noise* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_lattice_noise_set_m_color_1(lattice_noise* self, bool arg0) {
  self->m_color = arg0;
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

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_dotGridGradient_4(perlin_noise* self, int ix, int iy, float x, float y) {
  return self->dotGridGradient(ix, iy, x, y);
}

perlin_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_perlin_noise_4(float frequency, int noise_grid_resolution, int seed, bool color) {
  return new perlin_noise(frequency, noise_grid_resolution, seed, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_eval_2(perlin_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_calculate_noise_grid_0(perlin_noise* self) {
  self->calculate_noise_grid();
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_rand_01_0(perlin_noise* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_array_index_3(perlin_noise* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_getImageArray_2(perlin_noise* self, int width, int height) {
  return self->getImageArray(width, height);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_frequency_0(perlin_noise* self) {
  return self->m_frequency;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_frequency_1(perlin_noise* self, float arg0) {
  self->m_frequency = arg0;
}

vector2* EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_vector_grid_1(perlin_noise* self, int arg0) {
  return self->m_vector_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_vector_grid_2(perlin_noise* self, int arg0, vector2* arg1) {
  self->m_vector_grid[arg0] = arg1;
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_noise_grid_1(perlin_noise* self, int arg0) {
  return self->m_noise_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_noise_grid_2(perlin_noise* self, int arg0, float arg1) {
  self->m_noise_grid[arg0] = arg1;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_noise_grid_resolution_0(perlin_noise* self) {
  return self->m_noise_grid_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_noise_grid_resolution_1(perlin_noise* self, int arg0) {
  self->m_noise_grid_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_seed_0(perlin_noise* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_seed_1(perlin_noise* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_get_m_color_0(perlin_noise* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise_set_m_color_1(perlin_noise* self, bool arg0) {
  self->m_color = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_perlin_noise___destroy___0(perlin_noise* self) {
  delete self;
}

// value_noise

value_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_value_noise_5(float frequency, int image_resolution, int noise_grid_resolution, int seed, bool color) {
  return new value_noise(frequency, image_resolution, noise_grid_resolution, seed, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_eval_2(value_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_calculate_noise_grid_0(value_noise* self) {
  self->calculate_noise_grid();
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_rand_01_0(value_noise* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_array_index_3(value_noise* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_getImageArray_2(value_noise* self, int width, int height) {
  return self->getImageArray(width, height);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_frequency_0(value_noise* self) {
  return self->m_frequency;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_frequency_1(value_noise* self, float arg0) {
  self->m_frequency = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_image_resolution_0(value_noise* self) {
  return self->m_image_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_image_resolution_1(value_noise* self, int arg0) {
  self->m_image_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_noise_mask_0(value_noise* self) {
  return self->m_noise_mask;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_noise_mask_1(value_noise* self, int arg0) {
  self->m_noise_mask = arg0;
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_noise_grid_1(value_noise* self, int arg0) {
  return self->m_noise_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_noise_grid_2(value_noise* self, int arg0, float arg1) {
  self->m_noise_grid[arg0] = arg1;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_noise_grid_resolution_0(value_noise* self) {
  return self->m_noise_grid_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_noise_grid_resolution_1(value_noise* self, int arg0) {
  self->m_noise_grid_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_seed_0(value_noise* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_seed_1(value_noise* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_get_m_color_0(value_noise* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise_set_m_color_1(value_noise* self, bool arg0) {
  self->m_color = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_value_noise___destroy___0(value_noise* self) {
  delete self;
}

// white_noise

float EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_eval_2(white_noise* self, float x, float y) {
  return self->eval(x, y);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_calculate_noise_grid_0(white_noise* self) {
  self->calculate_noise_grid();
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_rand_01_0(white_noise* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_get_array_index_3(white_noise* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_getImageArray_2(white_noise* self, int width, int height) {
  return self->getImageArray(width, height);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_get_m_noise_grid_1(white_noise* self, int arg0) {
  return self->m_noise_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_m_noise_grid_2(white_noise* self, int arg0, float arg1) {
  self->m_noise_grid[arg0] = arg1;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_get_m_noise_grid_resolution_0(white_noise* self) {
  return self->m_noise_grid_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_m_noise_grid_resolution_1(white_noise* self, int arg0) {
  self->m_noise_grid_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_get_m_seed_0(white_noise* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_m_seed_1(white_noise* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_get_m_color_0(white_noise* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise_set_m_color_1(white_noise* self, bool arg0) {
  self->m_color = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_white_noise___destroy___0(white_noise* self) {
  delete self;
}

// voronoi_noise

float EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_distance_2(voronoi_noise* self, vector2* a, vector2* b) {
  return self->distance(a, b);
}

voronoi_noise* EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_voronoi_noise_4(int image_resolution, int cell_amount, int seed, bool color) {
  return new voronoi_noise(image_resolution, cell_amount, seed, color);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_eval_2(voronoi_noise* self, float x, float y) {
  return self->eval(x, y);
}

float EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_rand_01_0(voronoi_noise* self) {
  return self->rand_01();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_array_index_3(voronoi_noise* self, int width, int row, int col) {
  return self->get_array_index(width, row, col);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_getImageArray_2(voronoi_noise* self, int width, int height) {
  return self->getImageArray(width, height);
}

vector2* EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_m_cell_grid_1(voronoi_noise* self, int arg0) {
  return self->m_cell_grid[arg0];
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_m_cell_grid_2(voronoi_noise* self, int arg0, vector2* arg1) {
  self->m_cell_grid[arg0] = arg1;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_m_cell_amount_0(voronoi_noise* self) {
  return self->m_cell_amount;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_m_cell_amount_1(voronoi_noise* self, int arg0) {
  self->m_cell_amount = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_m_image_resolution_0(voronoi_noise* self) {
  return self->m_image_resolution;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_m_image_resolution_1(voronoi_noise* self, int arg0) {
  self->m_image_resolution = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_m_seed_0(voronoi_noise* self) {
  return self->m_seed;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_m_seed_1(voronoi_noise* self, int arg0) {
  self->m_seed = arg0;
}

bool EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_get_m_color_0(voronoi_noise* self) {
  return self->m_color;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise_set_m_color_1(voronoi_noise* self, bool arg0) {
  self->m_color = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_voronoi_noise___destroy___0(voronoi_noise* self) {
  delete self;
}

}

