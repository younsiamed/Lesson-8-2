#include <iostream>
#include <algorithm>

class TextComponent {
public:
    virtual ~TextComponent() = default;
    virtual void render(const std::string& text) const = 0;
};

class Text : public TextComponent {
public:
    void render(const std::string& text) const override {
        std::cout << text;
    }
};

class TextDecorator : public TextComponent {
protected:
    TextComponent* component;
public:
    TextDecorator(TextComponent* component) : component(component) {}
    virtual ~TextDecorator() {
        delete component;
    }
    void render(const std::string& text) const override {
        component->render(text);
    }
};

class Paragraph : public TextDecorator {
public:
    Paragraph(TextComponent* component) : TextDecorator(component) {}

    void render(const std::string& text) const override {
        std::cout << "<p>";
        TextDecorator::render(text);
        std::cout << "</p>";
    }
};

class Reversed : public TextDecorator {
public:
    Reversed(TextComponent* component) : TextDecorator(component) {}

    void render(const std::string& text) const override {
        std::string reversed_text = text;
        std::reverse(reversed_text.begin(), reversed_text.end());
        TextDecorator::render(reversed_text);
    }
};

class Link : public TextDecorator {
public:
    Link(TextComponent* component) : TextDecorator(component) {}

    void render(const std::string& url, const std::string& text) const {
        std::cout << "<a href=\"" << url << "\">";
        TextDecorator::render(text);
        std::cout << "</a>";
    }
};

int main() {
    TextComponent* text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    std::cout << std::endl;

    TextComponent* text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << std::endl;

    Link* text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
    std::cout << std::endl;

    delete text_block1;
    delete text_block2;
    delete text_block3;

    return 0;
}
