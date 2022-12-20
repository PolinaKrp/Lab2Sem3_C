#include "template.cpp"


template <typename T>
void Make_Line(int x1, int y1, int x2, int y2, BinaryImg<T>& src)
{
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { throw EClassException("working with numbers greater than zero"); }
    if (x1 >= src.GetRow() || x2 >= src.GetRow() || y1 >= src.GetCol() || y2 >= src.GetCol()) {
        throw EClassException("Coordinates out of range");
    }
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int error = dx + dy;

    while (true)
    {
        src(x1, y1) = std::numeric_limits<T>::max();
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x1 == x2) break;
            error = error + dy;
            x1 = x1 + sx;
        }
        if (e2 <= dx)
        {
            if (y1 == y2) break;
            error = error + dx;
            y1 = y1 + sy;
        }
    }
}


template <>
void Make_Line(int x1, int y1, int x2, int y2, BinaryImg<char>& src)
{
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) { throw EClassException("working with numbers greater than zero"); }
    if (x1 >= src.GetRow() || x2 >= src.GetRow() || y1 >= src.GetCol() || y2 >= src.GetCol()) {
        throw EClassException("Coordinates out of range");
    }
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int error = dx + dy;

    while (true)
    {
        src(x1, y1) = std::numeric_limits<char>::max();
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x1 == x2) break;
            error = error + dy;
            x1 = x1 + sx;
        }
        if (e2 <= dx)
        {
            if (y1 == y2) break;
            error = error + dx;
            y1 = y1 + sy;
        }
    }
}


void PrintMenu()
{
    system("cls");
    std::cout << "1. Template Bool" << std::endl;
    std::cout << "2. Template Char" << std::endl;
    std::cout << "3. Template Short" << std::endl;
    std::cout << "4. Template float" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "choice: ";
}

void PrintMenu1()
{
    system("cls");
    std::cout << "Make a choice:" << std::endl;
    std::cout << "1. Fill the image" << std::endl;
    std::cout << "2. Read the element" << std::endl;
    std::cout << "3. Invert the image" << std::endl;
    std::cout << "4. Multiply by Img" << std::endl;
    std::cout << "5. Multiply by value" << std::endl;
    std::cout << "6. Addition with Img" << std::endl;
    std::cout << "7. Addition with value" << std::endl;
    std::cout << "8. FillFactoricient occupacity" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "choice: ";
}


int main()
{
    int row = 0, col = 0;
    int choice = 0;
    bool exit = false;
    while (!exit)
    {
        PrintMenu();
        std::cin >> choice;
        switch (choice)
        {
        case(1):
            std::cout << "Enter dimenstion of your image:" << std::endl;
            try
            {
                std::cout << "Enter row: ";
                std::cin >> row;
                std::cout << "Enter col: ";
                std::cin >> col;

                BinaryImg<bool> image(row, col);
                int choice1 = 0;
                bool exit1 = false;
                while (!exit1)
                {
                    PrintMenu1();
                    std::cin >> choice1;
                    if (choice1 == 1) {
                        try {
                            int x, y;
                            bool temp = false;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;
                            std::cout << "Enter value: ";
                            std::cin >> temp;
                            image(x, y) = temp;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 2) {
                        try {
                            int x, y;
                            bool temp = false;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;

                            temp = image(x, y);
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 3) {
                        try {
                            BinaryImg<bool> temp(row, col);
                            temp = !image;
                            image = temp;
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 4) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<bool> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<bool>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<bool> res(sx, sy);
                            res = image * b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 5) {
                        try {
                            std::cout << "Enter value:";
                            bool c;
                            std::cin >> c;
                            BinaryImg<bool> res(row, col);
                            res = image * c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 6) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<bool> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<bool>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<bool> res(sx, sy);
                            res = image + b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 7) {
                        try {
                            std::cout << "Enter value:";
                            bool c;
                            std::cin >> c;
                            BinaryImg<bool> res(row, col);
                            res = image + c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 8) {
                        double res;
                        res = image.FillFactor();
                        std::cout.precision(2);
                        std::cout << res << std::endl;
                        system("pause");
                    }

                    else if (choice1 == 9) {
                        exit1 = true;
                    }
                    else
                    {
                        std::cout << "Error";
                    }
                }
            }
            catch (EClassException& err)
            {
                err.Print();
                system("pause");
            }

            break;
        case(2):
            std::cout << "Enter dimenstion of your image:" << std::endl;
            try
            {
                std::cout << "Enter row: ";
                std::cin >> row;
                std::cout << "Enter col: ";
                std::cin >> col;

                BinaryImg<char> image(row, col);
                int choice1 = 0;
                bool exit1 = false;
                while (!exit1)
                {
                    PrintMenu1();
                    std::cin >> choice1;
                    if (choice1 == 1) {
                        try {
                            int x, y;
                            char temp = '0';
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;
                            std::cout << "Enter value: ";
                            std::cin >> temp;
                            image(x, y) = temp;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 2) {
                        try {
                            int x, y;
                            char temp = '0';
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;

                            temp = image(x, y);
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 3) {
                        try {
                            BinaryImg<char> temp(row, col);
                            temp = !image;
                            image = temp;
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 4) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<char> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<char>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<char> res(sx, sy);
                            res = image * b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 5) {
                        try {
                            std::cout << "Enter value:";
                            char c;
                            std::cin >> c;
                            BinaryImg<char> res(row, col);
                            res = image * c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 6) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<char> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<char>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<char> res(sx, sy);
                            res = image + b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 7) {
                        try {
                            std::cout << "Enter value:";
                            char c;
                            std::cin >> c;
                            BinaryImg<char> res(row, col);
                            res = image + c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 8) {
                        double res;
                        res = image.FillFactor();
                        std::cout.precision(2);
                        std::cout << res << std::endl;
                        system("pause");
                    }

                    else if (choice1 == 9) {
                        exit1 = true;
                    }
                    else
                    {
                        std::cout << "Error";
                    }
                }
            }
            catch (EClassException& err)
            {
                err.Print();
                system("pause");
            }
            break;
        case(3):
            std::cout << "Enter dimenstion of your image:" << std::endl;
            try
            {
                std::cout << "Enter row: ";
                std::cin >> row;
                std::cout << "Enter col: ";
                std::cin >> col;

                BinaryImg<short> image(row, col);
                int choice1 = 0;
                bool exit1 = false;
                while (!exit1)
                {
                    PrintMenu1();
                    std::cin >> choice1;
                    if (choice1 == 1) {
                        try {
                            int x, y;
                            short temp = 0;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;
                            std::cout << "Enter value: ";
                            std::cin >> temp;
                            image(x, y) = temp;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 2) {
                        try {
                            int x, y;
                            short temp = 0;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;

                            temp = image(x, y);
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 3) {
                        try {
                            BinaryImg<short> temp(row, col);
                            temp = !image;
                            image = temp;
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 4) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<short> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<short>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<short> res(sx, sy);
                            res = image * b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 5) {
                        try {
                            std::cout << "Enter value:";
                            short c;
                            std::cin >> c;
                            BinaryImg<short> res(row, col);
                            res = image * c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 6) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<short> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<short>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<short> res(sx, sy);
                            res = image + b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 7) {
                        try {
                            std::cout << "Enter value:";
                            short c;
                            std::cin >> c;
                            BinaryImg<short> res(row, col);
                            res = image + c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 8) {
                        double res;
                        res = image.FillFactor();
                        std::cout.precision(2);
                        std::cout << res << std::endl;
                        system("pause");
                    }

                    else if (choice1 == 9) {
                        exit1 = true;
                    }
                    else
                    {
                        std::cout << "Error";
                    }
                }
            }
            catch (EClassException& err)
            {
                err.Print();
                system("pause");
            }
            break;
        case(4):
            std::cout << "Enter dimenstion of your image:" << std::endl;
            try
            {
                std::cout << "Enter row: ";
                std::cin >> row;
                std::cout << "Enter col: ";
                std::cin >> col;

                BinaryImg<float> image(row, col);
                int choice1 = 0;
                bool exit1 = false;
                while (!exit1)
                {
                    PrintMenu1();
                    std::cin >> choice1;
                    if (choice1 == 1) {
                        try {
                            int x, y;
                            float temp = 0;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;
                            std::cout << "Enter value: ";
                            std::cin >> temp;
                            image(x, y) = temp;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 2) {
                        try {
                            int x, y;
                            float temp = 0;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x: ";
                            std::cin >> x;
                            std::cout << "enter y: ";
                            std::cin >> y;

                            temp = image(x, y);
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 3) {
                        try {
                            BinaryImg<float> temp(row, col);
                            temp = !image;
                            image = temp;
                            std::cout << temp;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 4) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<float> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<float>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<float> res(sx, sy);
                            res = image * b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 5) {
                        try {
                            std::cout << "Enter value:";
                            float c;
                            std::cin >> c;
                            BinaryImg<float> res(row, col);
                            res = image * c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 6) {
                        try {
                            std::cout << "Enter dimenstion of your image:" << std::endl;
                            int sx, sy;
                            std::cout << "enter x: ";
                            std::cin >> sx;
                            std::cout << "enter y: ";
                            std::cin >> sy;
                            BinaryImg<float> b(sx, sy);
                            std::cout << "Enter the coordinates of the line:" << std::endl;
                            int sx1, sy1, sx2, sy2;
                            std::cout << "Enter coordinates of element: " << std::endl;
                            std::cout << "enter x1 and y1: ";
                            std::cin >> sx1 >> sy1;
                            std::cout << "enter x2 and y2: ";
                            std::cin >> sx2 >> sy2;
                            Make_Line<float>(sx1, sy1, sx2, sy2, b);
                            BinaryImg<float> res(sx, sy);
                            res = image + b;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 7) {
                        try {
                            std::cout << "Enter value:";
                            float c;
                            std::cin >> c;
                            BinaryImg<float> res(row, col);
                            res = image + c;
                            image = res;
                            std::cout << image;
                            system("pause");
                        }
                        catch (EClassException& err)
                        {
                            err.Print();
                            system("pause");
                        }
                    }
                    else if (choice1 == 8) {
                        double res;
                        res = image.FillFactor();
                        std::cout.precision(2);
                        std::cout << res << std::endl;
                        system("pause");
                    }

                    else if (choice1 == 9) {
                        exit1 = true;
                    }
                    else
                    {
                        std::cout << "Error";
                    }
                }
            }
            catch (EClassException& err)
            {
                err.Print();
                system("pause");
            }
            break;
        case(5):
            exit = true;
            break;
        default:
            std::cout << "Error";
            break;
        }
    }

    return 1;
}

