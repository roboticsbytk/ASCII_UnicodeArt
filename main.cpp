/*
 * Created by roboticsbytk
 * Date: 7/10/2020
 * Website: roboticsbytk.blogspot.com
 *
 * This a .cpp file that converts your image to ASCII/UNICODE art and prints it to a text file
 */
#include <locale>
#include <codecvt>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <wchar.h>
using namespace std;

int main()
{   //Instantiate an image variable using the SFML sf::Image class
    sf::Image image;

    //path to your image

    //IMPORTANT:- Your image should preferably be GRAYSCALE
    //         :- This program is CONTRAST DEPENDENT (adjust the contrast in an image editor software.
    //                                                 although, you can try out without adjusting the contrast first.)
    string path="kermiti1.jpg";

    //checks to see if image has correctly loaded
    if (!image.loadFromFile(path))
    {
        return -1;
    }
    //samples the pixels at a certain resolution
    //TIP: Every image is different, certain images may print out better with bigger or smaller resolutions
    //Xresolution and Yresolution can be considered independent
    //It varies on a case by case basis, if you dont choose a correct value your image will be WONKY
    int Xresolution=4;
    int Yresolution=2;



    //Ordered Character String obtained from source (URL:https://marmelab.com/blog/2018/02/20/convert-image-to-ascii-art-masterpiece.html)
    //Original Character string with ASCII only characters
    //L"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,^`'.";

    //The one I used includes several Urdu and Arabic characters
    // \u0621 is ء(hamza)
    // \u0684 is ه (heh)
    // \u076f is ݯ (hah with two dots) (this character isnt used in the Urdu language)
    // \u0628 is ب (bay)
    // \u0646 is ن (noon)

    wchar_t charset1[]=L"$@B%8&WM\u076f\u0628#*oahkbdpqwmeZO0QLCJUYXzcvunxrjft/\|\u0646()1{}[]?-_+~<>i!lI;:,^\u0621`'\u0684 .";
    //char_set will store the character that we want to print out
    wchar_t char_place;
    //Depending on the intensity of the pixel, we find a corresponding character from charset1. index will store the index
    //value of the character
    int index;
    //imagedata is used to store the grayscale value of each pixel from the image (0-255)
    int imagedata;

    //Because we want the Unicode codepoints to be printed properly in our text file, we need to make sure they are encoded
    //in UTF-8, which can handle Unicode characters' encoding.
    //A UTF-8 locale is defined
    const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
    wofstream f("sample.txt"); // we need to use wofstream because wide characters are being printed
    f.imbue(utf8_locale);//the locale is imbued to the stream
    f.clear();  //clears previous entries  in the file


    //The following code loops through each pixel
    for(int i=Yresolution; i<=(image.getSize().y-Yresolution) ;  i+=Yresolution) // converts each pixel to grayscale with weights
    {
        for(int j=Xresolution; j<=(image.getSize().x-Xresolution);  j+=Xresolution)
        {
            imagedata=image.getPixel(j,i).r*0.21+0.72*image.getPixel(j,i).g+0.07*image.getPixel(j,i).b; //converts each pixel to grayscale
            index=((int)((((wcslen(charset1))-1)*(imagedata/255.f)*1 ))); //finds corresponding character depending on grayscale value from the intensity-sorted character set
            char_place=charset1[index]; //sets character to the wchar_t variable
            f<<char_place<<"  \a"; //prints the character, a space is added to make sure the Urdu characters dont collate
        }
        f<<"\r\n"; // skips line after each row
    }
    f.close(); //closes file
    return 0;
}
