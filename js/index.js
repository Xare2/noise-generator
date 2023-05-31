const NOISE_SIZE = 512;

let module_instance = null;
let noise_module = null;

Module().then(Module => {
    module_instance = Module;

    setPerlinNoise();
});

function setCanvasTexture(noise_module) {
    if (module_instance === null)
        return;

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    const cWidth = canvas.clientWidth;
    const cHeight = canvas.clientHeight;
    const imageData = ctx.createImageData(cWidth, cHeight)

    let idx = 0;
    for (let i = 0; i < NOISE_SIZE; i++)
        for (let j = 0; j < NOISE_SIZE; j++) {
            let c = noise_module.eval(j, i);

            imageData.data[idx + 0] = (c * 255);
            imageData.data[idx + 1] = (c * 255);
            imageData.data[idx + 2] = (c * 255);
            imageData.data[idx + 3] = (255);

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

function onSeedChanged() {
    if (noise_module === null) return;

    noise_module.set_seed(getSeed());
    setCanvasTexture(noise_module);
}

function getFrequency() {
    return document.getElementById('frequency-slider').value;
}

function onFrequencyChange() {
    if (noise_module === null) return;

    noise_module.set_frequency(getFrequency() / 100);
    setCanvasTexture(noise_module);
}

function onCellDensityChange() {
    if (noise_module === null) return;

    noise_module.set_cell_amount(document.getElementById('cell-density').value);
    setCanvasTexture(noise_module);
}

// perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
function setPerlinNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);
    noise_module = new module_instance.perlin_noise(getFrequency() / 100, NOISE_SIZE, getSeed(), false);

    setValueVisibility(false);
    setPerlinVisibility(true);
    setVoronoiVisibility(false);

    setCanvasTexture(noise_module);
}

// value_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
function setValueNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);
    noise_module = new module_instance.value_noise(getFrequency() / 100, NOISE_SIZE, getSeed(), false);

    setValueVisibility(true);
    setPerlinVisibility(false);
    setVoronoiVisibility(false);

    setCanvasTexture(noise_module);
}

// voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color);
function setVoronoiNoise() {
    if (noise_module !== null)
        module_instance.destroy(noise_module);
    noise_module = new module_instance.voronoi_noise(NOISE_SIZE, 10, 0, false);

    setValueVisibility(false);
    setPerlinVisibility(false);
    setVoronoiVisibility(true);

    setCanvasTexture(noise_module);
}