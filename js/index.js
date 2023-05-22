Module().then(Module => {
    // let b = new Module.Bar(123);
    // b.doSomething();

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    const cWidth = canvas.clientWidth;
    const cHeight = canvas.clientHeight;
    const imageData = ctx.createImageData(cWidth, cHeight)

    // float frequency, unsigned noise_grid_resolution, unsigned seed, bool color
    let pn = new Module.perlin_noise(.05, cWidth, 10, false);

    let imgData = Array();

    let idx = 0;
    for (let i = 0; i < cWidth; i++)
        for (let j = 0; j < cHeight; j++) {
            let c = pn.eval(j, i);

            imageData.data[idx + 0] = (c * 255);
            imageData.data[idx + 1] = (c * 255);
            imageData.data[idx + 2] = (c * 255);
            imageData.data[idx + 3] = (255);

            idx += 4;
        }

    // imageData.data = imgData;

    ctx.putImageData(imageData, 0, 0);
});