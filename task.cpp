#include <iostream>
#include <limits>
#include <string>

class Tree {
protected:
    int height;

    virtual char getFillCharacter() const = 0;

    virtual void drawTrunk() const {
        for (int i = 0; i < height - 1; ++i) {
            std::cout << " ";
        }
        if (height > 0) {
             std::cout << "##\n";
        }
    }

public:
    explicit Tree(int h) : height(h) {
        if (height < 1) {
             height = 1;
        }
    }

    virtual ~Tree() {}

    virtual void draw() const {
        if (height <= 0) return;

        for (int layer = 0; layer < height; ++layer) {
            int spaces = height - 1 - layer;
            for (int i = 0; i < spaces; ++i) {
                std::cout << " ";
            }
            std::cout << "/";

            char fillChar = getFillCharacter();

            int innerWidth = 2 * layer;
            for (int i = 0; i < innerWidth; ++i) {
                std::cout << fillChar;
            }
            std::cout << "\\\n";
        }
        drawTrunk();
    }

    int getHeight() const { return height; }
};

class SpruceTree : public Tree {
public:
    explicit SpruceTree(int h) : Tree(h) {}

    char getFillCharacter() const override {
        return '/';
    }

    ~SpruceTree() {}
};

class PineTree : public Tree {
public:
    explicit PineTree(int h) : Tree(h) {}

    char getFillCharacter() const override {
        return '*';
    }

    ~PineTree() {}
};

class OakTree : public Tree {
public:
    explicit OakTree(int h) : Tree(h) {}

    char getFillCharacter() const override {
        return '+';
    }

    ~OakTree() {}
};

int getIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good()) {
            char remaining = std::cin.peek();
            if (remaining == '\n' || remaining == ' ') {
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 return value;
            }
        }
        std::cout << "Помилка: Будь ласка, введіть тільки ціле число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int getPositiveHeightInput(const std::string& treeName) {
     int height;
     while(true) {
        height = getIntegerInput("Введіть бажану висоту для '" + treeName + "' (> 0): ");
        if (height > 0) {
            return height;
        }
        std::cout << "Помилка: Висота повинна бути більшою за 0.\n";
     }
}

int main() {
    std::cout << "--- Вічний Малювальник Дерев ---\n";
    std::cout << "(Натисніть Ctrl+C для виходу)\n\n";

    while (true) {
        int height;
        Tree* treePtr = nullptr;

        height = getPositiveHeightInput("Ялинка");
        treePtr = new SpruceTree(height);
        std::cout << "\n--- Малюємо Ялинку (Висота: " << height << ") ---\n";
        treePtr->draw();
        delete treePtr;
        treePtr = nullptr;
        std::cout << "-------------------------------------\n" << std::endl;

        height = getPositiveHeightInput("Сосна");
        treePtr = new PineTree(height);
        std::cout << "\n--- Малюємо Сосну (Висота: " << height << ") ---\n";
        treePtr->draw();
        delete treePtr;
        treePtr = nullptr;
        std::cout << "-------------------------------------\n" << std::endl;

        height = getPositiveHeightInput("Дуб");
        treePtr = new OakTree(height);
        std::cout << "\n--- Малюємо Дуб (Висота: " << height << ") ---\n";
        treePtr->draw();
        delete treePtr;
        treePtr = nullptr;
        std::cout << "-------------------------------------\n" << std::endl;
    }
}
