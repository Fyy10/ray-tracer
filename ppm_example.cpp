// generate an example ppm image content, output as plain text
#include <iostream>
using namespace std;

int main() {
    // image size
    const int image_width = 256;
    const int image_height = 256;

    // header
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // content
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            cout << i << ' ' << j << ' ' << 100 << '\n';
        }
    }

    return 0;
}
