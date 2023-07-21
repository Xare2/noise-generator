let module_instance = null;
let noise_module = null;
let array = null;
Module().then(Module => {
    module_instance = Module;

    setPerlinNoise();
});

function setCanvasTexture(noise_module) {
    console.log("set texture called");
    if (module_instance === null)
        return;

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    const cWidth = canvas.width;
    const cHeight = canvas.height;
    const imageData = ctx.createImageData(cWidth, cHeight)

    // const data = noise_module.get_image_data();
    // array = new Uint8Array(cWidth * cHeight * 4);
    // noise_module.populate_image_data(array);
    // imageData.data = array;
    let idx = 0;
    for (let i = 0; i < cWidth; i++)
        for (let j = 0; j < cHeight; j++) {
            let c = noise_module.eval(j, i);

            imageData.data[idx + 0] = c * 255;
            imageData.data[idx + 1] = c * 255;;
            imageData.data[idx + 2] = c * 255;;
            imageData.data[idx + 3] = 255;
            // imageData.data[idx + 0] = noise_module.get_image_data(idx + 0);
            // imageData.data[idx + 1] = noise_module.get_image_data(idx + 1);
            // imageData.data[idx + 2] = noise_module.get_image_data(idx + 2);
            // imageData.data[idx + 3] = noise_module.get_image_data(idx + 3);

            idx += 4;
        }
    ctx.putImageData(imageData, 0, 0);
}

function onNoiseTypeChanged() {
    if (module_instance === null)
        return;

    const select = document.getElementById('noise-type');

    switch (select.options[select.selectedIndex].value) {
        case 'perlin':
            setPerlinNoise();
            break;
        case "value":
            setValueNoise();
            break;
        case "voronoi":
            setVoronoiNoise();
            break;
    }
}

function getResolution() {
    const select = document.getElementById('resolution');
    return select.options[select.selectedIndex].value;
}

function onResolutionChanged(value) {
    if (module_instance === null)
        return;

    let canvas = document.getElementById('canvas');

    canvas.width = value;
    canvas.height = value;

    noise_module.set_resolution(value);
    setCanvasTexture(noise_module);
}

function setPerlinVisibility(visible) {
    document.getElementById('perlin-input').style.display = visible ? 'flex' : 'none';
}

function setValueVisibility(visible) {
    document.getElementById('value-input').style.display = visible ? 'flex' : 'none';
}

function setVoronoiVisibility(visible) {
    document.getElementById('voronoi-input').style.display = visible ? 'flex' : 'none';
}

function getSeed() {
    return document.getElementById('seed').value;
}

function onSeedChanged(value) {
    if (noise_module === null) return;

    noise_module.set_seed(value);
    setCanvasTexture(noise_module);
}

function getFrequency() {
    return document.getElementById('frequency-slider').value;
}

function onFrequencyChange(value) {
    if (noise_module === null) return;

    noise_module.set_frequency(value / 100);
    setCanvasTexture(noise_module);
}

function onCellDensityChange(value) {
    if (noise_module === null) return;

    noise_module.set_cell_amount(value);
    setCanvasTexture(noise_module);
}

// perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
function setPerlinNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);

    setValueVisibility(false);
    setPerlinVisibility(true);
    setVoronoiVisibility(false);

    noise_module = new module_instance.perlin_noise(getFrequency() / 100, getResolution(), getSeed(), false);

    setCanvasTexture(noise_module);
}

// value_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
function setValueNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);

    setValueVisibility(true);
    setPerlinVisibility(false);
    setVoronoiVisibility(false);

    noise_module = new module_instance.value_noise(getFrequency() / 100, getResolution(), getSeed(), false);

    setCanvasTexture(noise_module);
}

// voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color);
function setVoronoiNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);

    setValueVisibility(false);
    setPerlinVisibility(false);
    setVoronoiVisibility(true);

    noise_module = new module_instance.voronoi_noise(getResolution(), 10, 0, false);

    setCanvasTexture(noise_module);
}