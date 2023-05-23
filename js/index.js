const NOISE_SIZE = 512;

let module_instance = null;

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
    for (let i = 0; i < cWidth; i++)
        for (let j = 0; j < cHeight; j++) {
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

// perlin_noise(float frequency, unsigned noise_grid_resolution, unsigned seed, bool color);
function setPerlinNoise() {
    let noise_module = new module_instance.perlin_noise(.05, NOISE_SIZE, 10, false);

    setCanvasTexture(noise_module);
}

// value_noise(float frequency, unsigned image_resolution, unsigned noise_grid_resolution, unsigned seed, bool color);
function setValueNoise() {
    let noise_module = new module_instance.value_noise(.05, NOISE_SIZE, NOISE_SIZE, 0, false);

    setCanvasTexture(noise_module);
}
// voronoi_noise(unsigned image_resolution, unsigned cell_amount, unsigned seed, bool color);
function setVoronoiNoise() {
    let noise_module = new module_instance.voronoi_noise(NOISE_SIZE, 10, 0, false);

    setCanvasTexture(noise_module);
}