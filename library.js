
mergeInto(
  LibraryManager.library,
  (function() {
    var canvasWidth=0;
    var canvasHeight =0;
    var canvas=null;
    var ctx =null;
    var imageData =null;
    var buf = null;
    var buf8 = null;
    var data= null;

    return {
      window_canvas_paint_init_em:function(w,h) {
        canvas = document.getElementById('canvas');
        canvasWidth  = canvas.width;
        canvasHeight = canvas.height;
        ctx = canvas.getContext('2d');
        imageData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);

        // buf = new ArrayBuffer(imageData.data.length);
        // buf8 = new Uint8ClampedArray(buf);
        // data = new Uint32Array(buf);
        data = imageData.data;

        ctx.font = "16px Arial";
        ctx.fillStyle = 'yellow';
      },

      window_canvas_paint : function(surfaceData,text) {
        for(var i=0;i<canvasWidth*canvasHeight*4;i++) {
          //buf8[i]=Module.HEAPU8[surfaceData+ i];
          data[i]=Module.HEAPU8[surfaceData+ i];
        }

        // for(var i=0;i<canvasWidth*canvasHeight;i++) {
        //   data2[i]=Module.HEAPU32[surfaceData+ i*4];
        // }

        //imageData.data.set(buf8);

        ctx.putImageData(imageData, 0, 0);

        var str=Pointer_stringify(text);
        ctx.fillText(str,1,16);

      }
    }
  })()
);