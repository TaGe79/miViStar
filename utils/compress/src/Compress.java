import org.junit.Assert;
import org.junit.Test;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * User: tgergel
 * Date: 17/09/14
 * Time: 23:59
 * To change this template use File | Settings | File Templates.
 */
public class Compress {
    private final static int[] sprite = new int[]{
//            1,0,0,1,
//            0,1,1,0,
//            0,1,1,0,
//            1,0,0,1

//            0,1,1,0,
//            1,0,0,1,
//            1,0,0,1,
//            0,1,1,0

            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,
            0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
            1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,
            1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1
    };

    private static int width = 40; //40; //4; //32;
    private static int height = 8; //40; //4; //32;

    private int[] jpgToByteArray() throws Exception {
        BufferedImage image = ImageIO.read(new File("/Users/tgergel/Documents/workspace/miViStar/pics/ViS.bmp"));
        int[] pixels = new int[image.getWidth()*image.getHeight()];

        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                int p = (int) (image.getRGB(x, y) == 0xFFFFFFFF ? 0 : 1);
                pixels[x+(y*image.getWidth())] = p;
                sb.append(p+",");
            }
            sb.append("\n");
        }

        System.out.println("Size: "+image.getWidth()+";"+image.getHeight());
        System.out.println(sb.toString());


        return pixels;
    }

    private int[] compress(int[] sprite, int width, int height) {
        final int codedLength = (width * height) / 8;
        final int bytesPerRow = width > 8 ? width/8 + ((width%8 == 0)?0: (8 / (width%8))) + ( (width%8 == 0 || 8 % (width%8) != 0 )?1:0 ) : 0;
        final int rowsPerByte = 8/width;

        int[] bytes = new int[codedLength];

        int currentByte = 0;
        int currentBit = 0;
        for ( int i = 0; i < width*height ; i++ ) {
            bytes[currentByte] = bytes[currentByte]+(sprite[i]<<(7-currentBit));
            currentBit += 1;
            currentBit %= 8;
            if ( currentBit == 0 ) currentByte+=1;
        }

        return bytes;
    }

    private int[] decompress(int[] bytes, int width, int height) {
        int wMacht = width % 8;
        final int bytesPerRow = width > 8 ? width/8 + ((wMacht == 0)?0: (8 / wMacht)) + ( (wMacht != 0 && 8 % wMacht != 0 )?1:0 ) : 0;
        final int rowsPerByte = 8/width;

        final int[] sprite = new int[width*height];
        int i=0;
        for ( int y =0; y<height; y++ ) {
            for ( int x=0; x<width; x++ ) {
                int idx = x/8 + ((bytesPerRow > 0)?y*bytesPerRow:y/rowsPerByte);
                int bit = (bytesPerRow > 0 ) ? 7- x%8 : 7 - (x%8 + (y%rowsPerByte)*width);
                int pix = (bytes[idx]>>bit)&0x01;
                sprite[i++] = pix;
            }
        }

        return sprite;
    }


    @Test
    public void testJpgToByteArray() throws Exception {
        jpgToByteArray();
    }

    @Test
    public void testSpriteCompression() {
        //assert width%8 == 0;

        int[] bytes = compress(sprite, width, height);

        final StringBuilder sb = new StringBuilder();
        for (int i =0; i<bytes.length; i++ ) {
            sb.append(String.format("0x%02X,",bytes[i]));
        }
        System.out.println("Compressed ("+bytes.length+"): "+sb.toString());
        int[] testSprite = decompress(bytes, width, height);

        Assert.assertArrayEquals(sprite,testSprite);
    }
}
