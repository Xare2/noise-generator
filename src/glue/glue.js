
// Bindings utilities

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function WrapperObject() {
}
WrapperObject.prototype = Object.create(WrapperObject.prototype);
WrapperObject.prototype.constructor = WrapperObject;
WrapperObject.prototype.__class__ = WrapperObject;
WrapperObject.__cache__ = {};
Module['WrapperObject'] = WrapperObject;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant)
    @param {*=} __class__ */
function getCache(__class__) {
  return (__class__ || WrapperObject).__cache__;
}
Module['getCache'] = getCache;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant)
    @param {*=} __class__ */
function wrapPointer(ptr, __class__) {
  var cache = getCache(__class__);
  var ret = cache[ptr];
  if (ret) return ret;
  ret = Object.create((__class__ || WrapperObject).prototype);
  ret.ptr = ptr;
  return cache[ptr] = ret;
}
Module['wrapPointer'] = wrapPointer;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function castObject(obj, __class__) {
  return wrapPointer(obj.ptr, __class__);
}
Module['castObject'] = castObject;

Module['NULL'] = wrapPointer(0);

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function destroy(obj) {
  if (!obj['__destroy__']) throw 'Error: Cannot destroy object. (Did you create it yourself?)';
  obj['__destroy__']();
  // Remove from cache, so the object can be GC'd and refs added onto it released
  delete getCache(obj.__class__)[obj.ptr];
}
Module['destroy'] = destroy;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function compare(obj1, obj2) {
  return obj1.ptr === obj2.ptr;
}
Module['compare'] = compare;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function getPointer(obj) {
  return obj.ptr;
}
Module['getPointer'] = getPointer;

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function getClass(obj) {
  return obj.__class__;
}
Module['getClass'] = getClass;

// Converts big (string or array) values into a C-style storage, in temporary space

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
var ensureCache = {
  buffer: 0,  // the main buffer of temporary storage
  size: 0,   // the size of buffer
  pos: 0,    // the next free offset in buffer
  temps: [], // extra allocations
  needed: 0, // the total size we need next time

  prepare: function() {
    if (ensureCache.needed) {
      // clear the temps
      for (var i = 0; i < ensureCache.temps.length; i++) {
        Module['_free'](ensureCache.temps[i]);
      }
      ensureCache.temps.length = 0;
      // prepare to allocate a bigger buffer
      Module['_free'](ensureCache.buffer);
      ensureCache.buffer = 0;
      ensureCache.size += ensureCache.needed;
      // clean up
      ensureCache.needed = 0;
    }
    if (!ensureCache.buffer) { // happens first time, or when we need to grow
      ensureCache.size += 128; // heuristic, avoid many small grow events
      ensureCache.buffer = Module['_malloc'](ensureCache.size);
      assert(ensureCache.buffer);
    }
    ensureCache.pos = 0;
  },
  alloc: function(array, view) {
    assert(ensureCache.buffer);
    var bytes = view.BYTES_PER_ELEMENT;
    var len = array.length * bytes;
    len = (len + 7) & -8; // keep things aligned to 8 byte boundaries
    var ret;
    if (ensureCache.pos + len >= ensureCache.size) {
      // we failed to allocate in the buffer, ensureCache time around :(
      assert(len > 0); // null terminator, at least
      ensureCache.needed += len;
      ret = Module['_malloc'](len);
      ensureCache.temps.push(ret);
    } else {
      // we can allocate in the buffer
      ret = ensureCache.buffer + ensureCache.pos;
      ensureCache.pos += len;
    }
    return ret;
  },
  copy: function(array, view, offset) {
    offset >>>= 0;
    var bytes = view.BYTES_PER_ELEMENT;
    switch (bytes) {
      case 2: offset >>>= 1; break;
      case 4: offset >>>= 2; break;
      case 8: offset >>>= 3; break;
    }
    for (var i = 0; i < array.length; i++) {
      view[offset + i] = array[i];
    }
  },
};

/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureString(value) {
  if (typeof value === 'string') {
    var intArray = intArrayFromString(value);
    var offset = ensureCache.alloc(intArray, HEAP8);
    ensureCache.copy(intArray, HEAP8, offset);
    return offset;
  }
  return value;
}
/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureInt8(value) {
  if (typeof value === 'object') {
    var offset = ensureCache.alloc(value, HEAP8);
    ensureCache.copy(value, HEAP8, offset);
    return offset;
  }
  return value;
}
/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureInt16(value) {
  if (typeof value === 'object') {
    var offset = ensureCache.alloc(value, HEAP16);
    ensureCache.copy(value, HEAP16, offset);
    return offset;
  }
  return value;
}
/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureInt32(value) {
  if (typeof value === 'object') {
    var offset = ensureCache.alloc(value, HEAP32);
    ensureCache.copy(value, HEAP32, offset);
    return offset;
  }
  return value;
}
/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureFloat32(value) {
  if (typeof value === 'object') {
    var offset = ensureCache.alloc(value, HEAPF32);
    ensureCache.copy(value, HEAPF32, offset);
    return offset;
  }
  return value;
}
/** @suppress {duplicate} (TODO: avoid emitting this multiple times, it is redundant) */
function ensureFloat64(value) {
  if (typeof value === 'object') {
    var offset = ensureCache.alloc(value, HEAPF64);
    ensureCache.copy(value, HEAPF64, offset);
    return offset;
  }
  return value;
}


// noise_generator

noise_generator.prototype['proba_array'] = noise_generator.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_noise_generator_proba_array_2(self, array, size);
};;
/** @suppress {undefinedVars, duplicate} @this{Object} */function noise_generator(resolution, seed, color) {
  if (resolution && typeof resolution === 'object') resolution = resolution.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  this.ptr = _emscripten_bind_noise_generator_noise_generator_3(resolution, seed, color);
  getCache(noise_generator)[this.ptr] = this;
};;
noise_generator.prototype = Object.create(WrapperObject.prototype);
noise_generator.prototype.constructor = noise_generator;
noise_generator.prototype.__class__ = noise_generator;
noise_generator.__cache__ = {};
Module['noise_generator'] = noise_generator;

noise_generator.prototype['set_color'] = noise_generator.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_noise_generator_set_color_1(self, color);
};;

noise_generator.prototype['calculate_image_data'] = noise_generator.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_noise_generator_calculate_image_data_0(self);
};;

noise_generator.prototype['populate_image_data'] = noise_generator.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_noise_generator_populate_image_data_1(self, image);
};;

noise_generator.prototype['set_seed'] = noise_generator.prototype.set_seed = /** @suppress {undefinedVars, duplicate} @this{Object} */function(seed) {
  var self = this.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  _emscripten_bind_noise_generator_set_seed_1(self, seed);
};;

noise_generator.prototype['eval'] = noise_generator.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_noise_generator_eval_2(self, x, y);
};;

  noise_generator.prototype['get_image_data'] = noise_generator.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_noise_generator_get_image_data_1(self, arg0);
};
    noise_generator.prototype['set_image_data'] = noise_generator.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_noise_generator_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(noise_generator.prototype, 'image_data', { get: noise_generator.prototype.get_image_data, set: noise_generator.prototype.set_image_data });
  noise_generator.prototype['__destroy__'] = noise_generator.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_noise_generator___destroy___0(self);
};
// lattice_noise
/** @suppress {undefinedVars, duplicate} @this{Object} */function lattice_noise(noise_grid_resolution, seed, frequency, color) {
  if (noise_grid_resolution && typeof noise_grid_resolution === 'object') noise_grid_resolution = noise_grid_resolution.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  this.ptr = _emscripten_bind_lattice_noise_lattice_noise_4(noise_grid_resolution, seed, frequency, color);
  getCache(lattice_noise)[this.ptr] = this;
};;
lattice_noise.prototype = Object.create(noise_generator.prototype);
lattice_noise.prototype.constructor = lattice_noise;
lattice_noise.prototype.__class__ = lattice_noise;
lattice_noise.__cache__ = {};
Module['lattice_noise'] = lattice_noise;

lattice_noise.prototype['set_frequency'] = lattice_noise.prototype.set_frequency = /** @suppress {undefinedVars, duplicate} @this{Object} */function(frequency) {
  var self = this.ptr;
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  _emscripten_bind_lattice_noise_set_frequency_1(self, frequency);
};;

lattice_noise.prototype['set_resolution'] = lattice_noise.prototype.set_resolution = /** @suppress {undefinedVars, duplicate} @this{Object} */function(resolution) {
  var self = this.ptr;
  if (resolution && typeof resolution === 'object') resolution = resolution.ptr;
  _emscripten_bind_lattice_noise_set_resolution_1(self, resolution);
};;

lattice_noise.prototype['set_seed'] = lattice_noise.prototype.set_seed = /** @suppress {undefinedVars, duplicate} @this{Object} */function(seed) {
  var self = this.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  _emscripten_bind_lattice_noise_set_seed_1(self, seed);
};;

lattice_noise.prototype['proba_array'] = lattice_noise.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_lattice_noise_proba_array_2(self, array, size);
};;

lattice_noise.prototype['set_color'] = lattice_noise.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_lattice_noise_set_color_1(self, color);
};;

lattice_noise.prototype['calculate_image_data'] = lattice_noise.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_lattice_noise_calculate_image_data_0(self);
};;

lattice_noise.prototype['populate_image_data'] = lattice_noise.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_lattice_noise_populate_image_data_1(self, image);
};;

lattice_noise.prototype['eval'] = lattice_noise.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_lattice_noise_eval_2(self, x, y);
};;

  lattice_noise.prototype['get_image_data'] = lattice_noise.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_lattice_noise_get_image_data_1(self, arg0);
};
    lattice_noise.prototype['set_image_data'] = lattice_noise.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_lattice_noise_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(lattice_noise.prototype, 'image_data', { get: lattice_noise.prototype.get_image_data, set: lattice_noise.prototype.set_image_data });
  lattice_noise.prototype['__destroy__'] = lattice_noise.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_lattice_noise___destroy___0(self);
};
// VoidPtr
/** @suppress {undefinedVars, duplicate} @this{Object} */function VoidPtr() { throw "cannot construct a VoidPtr, no constructor in IDL" }
VoidPtr.prototype = Object.create(WrapperObject.prototype);
VoidPtr.prototype.constructor = VoidPtr;
VoidPtr.prototype.__class__ = VoidPtr;
VoidPtr.__cache__ = {};
Module['VoidPtr'] = VoidPtr;

  VoidPtr.prototype['__destroy__'] = VoidPtr.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_VoidPtr___destroy___0(self);
};
// perlin_noise
/** @suppress {undefinedVars, duplicate} @this{Object} */function perlin_noise(frequency, noise_grid_resolution, seed, color) {
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  if (noise_grid_resolution && typeof noise_grid_resolution === 'object') noise_grid_resolution = noise_grid_resolution.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  this.ptr = _emscripten_bind_perlin_noise_perlin_noise_4(frequency, noise_grid_resolution, seed, color);
  getCache(perlin_noise)[this.ptr] = this;
};;
perlin_noise.prototype = Object.create(lattice_noise.prototype);
perlin_noise.prototype.constructor = perlin_noise;
perlin_noise.prototype.__class__ = perlin_noise;
perlin_noise.__cache__ = {};
Module['perlin_noise'] = perlin_noise;

perlin_noise.prototype['set_seed'] = perlin_noise.prototype.set_seed = /** @suppress {undefinedVars, duplicate} @this{Object} */function(seed) {
  var self = this.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  _emscripten_bind_perlin_noise_set_seed_1(self, seed);
};;

perlin_noise.prototype['set_resolution'] = perlin_noise.prototype.set_resolution = /** @suppress {undefinedVars, duplicate} @this{Object} */function(resolution) {
  var self = this.ptr;
  if (resolution && typeof resolution === 'object') resolution = resolution.ptr;
  _emscripten_bind_perlin_noise_set_resolution_1(self, resolution);
};;

perlin_noise.prototype['eval'] = perlin_noise.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_perlin_noise_eval_2(self, x, y);
};;

perlin_noise.prototype['set_frequency'] = perlin_noise.prototype.set_frequency = /** @suppress {undefinedVars, duplicate} @this{Object} */function(frequency) {
  var self = this.ptr;
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  _emscripten_bind_perlin_noise_set_frequency_1(self, frequency);
};;

perlin_noise.prototype['proba_array'] = perlin_noise.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_perlin_noise_proba_array_2(self, array, size);
};;

perlin_noise.prototype['set_color'] = perlin_noise.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_perlin_noise_set_color_1(self, color);
};;

perlin_noise.prototype['calculate_image_data'] = perlin_noise.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_perlin_noise_calculate_image_data_0(self);
};;

perlin_noise.prototype['populate_image_data'] = perlin_noise.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_perlin_noise_populate_image_data_1(self, image);
};;

  perlin_noise.prototype['get_image_data'] = perlin_noise.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_perlin_noise_get_image_data_1(self, arg0);
};
    perlin_noise.prototype['set_image_data'] = perlin_noise.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_perlin_noise_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(perlin_noise.prototype, 'image_data', { get: perlin_noise.prototype.get_image_data, set: perlin_noise.prototype.set_image_data });
  perlin_noise.prototype['__destroy__'] = perlin_noise.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_perlin_noise___destroy___0(self);
};
// value_noise
/** @suppress {undefinedVars, duplicate} @this{Object} */function value_noise(frequency, noise_grid_resolution, seed, color) {
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  if (noise_grid_resolution && typeof noise_grid_resolution === 'object') noise_grid_resolution = noise_grid_resolution.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  this.ptr = _emscripten_bind_value_noise_value_noise_4(frequency, noise_grid_resolution, seed, color);
  getCache(value_noise)[this.ptr] = this;
};;
value_noise.prototype = Object.create(lattice_noise.prototype);
value_noise.prototype.constructor = value_noise;
value_noise.prototype.__class__ = value_noise;
value_noise.__cache__ = {};
Module['value_noise'] = value_noise;

value_noise.prototype['eval'] = value_noise.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_value_noise_eval_2(self, x, y);
};;

value_noise.prototype['set_frequency'] = value_noise.prototype.set_frequency = /** @suppress {undefinedVars, duplicate} @this{Object} */function(frequency) {
  var self = this.ptr;
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  _emscripten_bind_value_noise_set_frequency_1(self, frequency);
};;

value_noise.prototype['proba_array'] = value_noise.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_value_noise_proba_array_2(self, array, size);
};;

value_noise.prototype['set_color'] = value_noise.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_value_noise_set_color_1(self, color);
};;

value_noise.prototype['calculate_image_data'] = value_noise.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_value_noise_calculate_image_data_0(self);
};;

value_noise.prototype['populate_image_data'] = value_noise.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_value_noise_populate_image_data_1(self, image);
};;

  value_noise.prototype['get_image_data'] = value_noise.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_value_noise_get_image_data_1(self, arg0);
};
    value_noise.prototype['set_image_data'] = value_noise.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_value_noise_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(value_noise.prototype, 'image_data', { get: value_noise.prototype.get_image_data, set: value_noise.prototype.set_image_data });
  value_noise.prototype['__destroy__'] = value_noise.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_value_noise___destroy___0(self);
};
// white_noise
/** @suppress {undefinedVars, duplicate} @this{Object} */function white_noise() { throw "cannot construct a white_noise, no constructor in IDL" }
white_noise.prototype = Object.create(lattice_noise.prototype);
white_noise.prototype.constructor = white_noise;
white_noise.prototype.__class__ = white_noise;
white_noise.__cache__ = {};
Module['white_noise'] = white_noise;

white_noise.prototype['eval'] = white_noise.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_white_noise_eval_2(self, x, y);
};;

white_noise.prototype['set_frequency'] = white_noise.prototype.set_frequency = /** @suppress {undefinedVars, duplicate} @this{Object} */function(frequency) {
  var self = this.ptr;
  if (frequency && typeof frequency === 'object') frequency = frequency.ptr;
  _emscripten_bind_white_noise_set_frequency_1(self, frequency);
};;

white_noise.prototype['proba_array'] = white_noise.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_white_noise_proba_array_2(self, array, size);
};;

white_noise.prototype['set_color'] = white_noise.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_white_noise_set_color_1(self, color);
};;

white_noise.prototype['calculate_image_data'] = white_noise.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_white_noise_calculate_image_data_0(self);
};;

white_noise.prototype['populate_image_data'] = white_noise.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_white_noise_populate_image_data_1(self, image);
};;

  white_noise.prototype['get_image_data'] = white_noise.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_white_noise_get_image_data_1(self, arg0);
};
    white_noise.prototype['set_image_data'] = white_noise.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_white_noise_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(white_noise.prototype, 'image_data', { get: white_noise.prototype.get_image_data, set: white_noise.prototype.set_image_data });
  white_noise.prototype['__destroy__'] = white_noise.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_white_noise___destroy___0(self);
};
// voronoi_noise
/** @suppress {undefinedVars, duplicate} @this{Object} */function voronoi_noise(image_resolution, cell_amount, seed, color) {
  if (image_resolution && typeof image_resolution === 'object') image_resolution = image_resolution.ptr;
  if (cell_amount && typeof cell_amount === 'object') cell_amount = cell_amount.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  this.ptr = _emscripten_bind_voronoi_noise_voronoi_noise_4(image_resolution, cell_amount, seed, color);
  getCache(voronoi_noise)[this.ptr] = this;
};;
voronoi_noise.prototype = Object.create(noise_generator.prototype);
voronoi_noise.prototype.constructor = voronoi_noise;
voronoi_noise.prototype.__class__ = voronoi_noise;
voronoi_noise.__cache__ = {};
Module['voronoi_noise'] = voronoi_noise;

voronoi_noise.prototype['set_cell_amount'] = voronoi_noise.prototype.set_cell_amount = /** @suppress {undefinedVars, duplicate} @this{Object} */function(cell_amount) {
  var self = this.ptr;
  if (cell_amount && typeof cell_amount === 'object') cell_amount = cell_amount.ptr;
  _emscripten_bind_voronoi_noise_set_cell_amount_1(self, cell_amount);
};;

voronoi_noise.prototype['set_resolution'] = voronoi_noise.prototype.set_resolution = /** @suppress {undefinedVars, duplicate} @this{Object} */function(resolution) {
  var self = this.ptr;
  if (resolution && typeof resolution === 'object') resolution = resolution.ptr;
  _emscripten_bind_voronoi_noise_set_resolution_1(self, resolution);
};;

voronoi_noise.prototype['set_seed'] = voronoi_noise.prototype.set_seed = /** @suppress {undefinedVars, duplicate} @this{Object} */function(seed) {
  var self = this.ptr;
  if (seed && typeof seed === 'object') seed = seed.ptr;
  _emscripten_bind_voronoi_noise_set_seed_1(self, seed);
};;

voronoi_noise.prototype['eval'] = voronoi_noise.prototype.eval = /** @suppress {undefinedVars, duplicate} @this{Object} */function(x, y) {
  var self = this.ptr;
  if (x && typeof x === 'object') x = x.ptr;
  if (y && typeof y === 'object') y = y.ptr;
  return _emscripten_bind_voronoi_noise_eval_2(self, x, y);
};;

voronoi_noise.prototype['proba_array'] = voronoi_noise.prototype.proba_array = /** @suppress {undefinedVars, duplicate} @this{Object} */function(array, size) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof array == 'object') { array = ensureInt32(array); }
  if (size && typeof size === 'object') size = size.ptr;
  _emscripten_bind_voronoi_noise_proba_array_2(self, array, size);
};;

voronoi_noise.prototype['set_color'] = voronoi_noise.prototype.set_color = /** @suppress {undefinedVars, duplicate} @this{Object} */function(color) {
  var self = this.ptr;
  if (color && typeof color === 'object') color = color.ptr;
  _emscripten_bind_voronoi_noise_set_color_1(self, color);
};;

voronoi_noise.prototype['calculate_image_data'] = voronoi_noise.prototype.calculate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_voronoi_noise_calculate_image_data_0(self);
};;

voronoi_noise.prototype['populate_image_data'] = voronoi_noise.prototype.populate_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(image) {
  var self = this.ptr;
  ensureCache.prepare();
  if (typeof image == 'object') { image = ensureInt32(image); }
  _emscripten_bind_voronoi_noise_populate_image_data_1(self, image);
};;

  voronoi_noise.prototype['get_image_data'] = voronoi_noise.prototype.get_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  return _emscripten_bind_voronoi_noise_get_image_data_1(self, arg0);
};
    voronoi_noise.prototype['set_image_data'] = voronoi_noise.prototype.set_image_data = /** @suppress {undefinedVars, duplicate} @this{Object} */function(arg0, arg1) {
  var self = this.ptr;
  ensureCache.prepare();
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  _emscripten_bind_voronoi_noise_set_image_data_2(self, arg0, arg1);
};
    Object.defineProperty(voronoi_noise.prototype, 'image_data', { get: voronoi_noise.prototype.get_image_data, set: voronoi_noise.prototype.set_image_data });
  voronoi_noise.prototype['__destroy__'] = voronoi_noise.prototype.__destroy__ = /** @suppress {undefinedVars, duplicate} @this{Object} */function() {
  var self = this.ptr;
  _emscripten_bind_voronoi_noise___destroy___0(self);
};