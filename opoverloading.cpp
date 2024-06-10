#include <iostream>
using namespace std;

class PersegiPanjang {
private:
    float xmin, xmax, ymin, ymax;

public:
    PersegiPanjang(float x_center, float y_center, float width, float height) {
        xmin = x_center - width / 2;
        xmax = x_center + width / 2;
        ymin = y_center - height / 2;
        ymax = y_center + height / 2;
    }

    PersegiPanjang operator+(const PersegiPanjang &other) {
        if (this->operator==(other)) {
            float new_xmin = min(this->xmin, other.xmin);
            float new_xmax = max(this->xmax, other.xmax);
            float new_ymin = min(this->ymin, other.ymin);
            float new_ymax = max(this->ymax, other.ymax);
            return PersegiPanjang((new_xmin + new_xmax) / 2, (new_ymin + new_ymax) / 2, new_xmax - new_xmin, new_ymax - new_ymin);
        } else {
            cout << "Rectangles do not overlap, cannot combine." << endl;
            return *this;
        }
    }

    PersegiPanjang operator-(const PersegiPanjang &other) {
        if (this->operator==(other)) {
            float new_xmin = max(this->xmin, other.xmin);
            float new_xmax = min(this->xmax, other.xmax);
            float new_ymin = max(this->ymin, other.ymin);
            float new_ymax = min(this->ymax, other.ymax);
            return PersegiPanjang((new_xmin + new_xmax) / 2, (new_ymin + new_ymax) / 2, new_xmax - new_xmin, new_ymax - new_ymin);
        } else {
            cout << "Rectangles do not overlap, no intersection." << endl;
            return *this;
        }
    }

    PersegiPanjang operator++() {
        float width = (xmax - xmin) * 2;
        float height = (ymax - ymin) * 2;
        xmin = (xmin + xmax) / 2 - width / 2;
        xmax = (xmin + xmax) / 2 + width / 2;
        ymin = (ymin + ymax) / 2 - height / 2;
        ymax = (ymin + ymax) / 2 + height / 2;
        return *this;
    }

    PersegiPanjang operator--() {
        float width = (xmax - xmin) / 2;
        float height = (ymax - ymin) / 2;
        xmin = (xmin + xmax) / 2 - width / 2;
        xmax = (xmin + xmax) / 2 + width / 2;
        ymin = (ymin + ymax) / 2 - height / 2;
        ymax = (ymin + ymax) / 2 + height / 2;
        return *this;
    }

    float operator[](int index) {
        switch (index) {
            case 0: return xmin;
            case 1: return xmax;
            case 2: return ymin;
            case 3: return ymax;
            default: throw out_of_range("Index out of range");
        }
    }
    
    bool operator==(const PersegiPanjang &other) {
        return !(xmax < other.xmin || xmin > other.xmax || ymax < other.ymin || ymin > other.ymax);
    }

    void display() {
        cout << "xmin: " << xmin << ", xmax: " << xmax << ", ymin: " << ymin << ", ymax: " << ymax << endl;
    }
};

int main() {
    PersegiPanjang rect1(0, 0, 4, 4);
    PersegiPanjang rect2(1, 1, 2, 2);

    cout << "Rectangle 1: ";
    rect1.display();
    cout << "Rectangle 2: ";
    rect2.display();

    PersegiPanjang rect3 = rect1 + rect2;
    cout << "Combined Rectangle: ";
    rect3.display();

    PersegiPanjang rect4 = rect1 - rect2;
    cout << "Intersection Rectangle: ";
    rect4.display();

    ++rect1;
    cout << "Doubled Area Rectangle 1: ";
    rect1.display();

    --rect2;
    cout << "Halved Area Rectangle 2: ";
    rect2.display();

    cout << "Rectangle 1 properties: xmin=" << rect1[0] << ", xmax=" << rect1[1] << ", ymin=" << rect1[2] << ", ymax=" << rect1[3] << endl;

    if (rect1 == rect2) {
        cout << "Rectangles overlap." << endl;
    } else {
        cout << "Rectangles do not overlap." << endl;
    }

    return 0;
}
