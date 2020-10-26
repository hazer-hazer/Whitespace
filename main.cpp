#include <map>
#include <vector>

// Lexer-Parser level
enum class TokenType {
    Push,
    Dup,
    Swap,
    Disc,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Store,
    Load,
    Mark,
    Call,
    Jump,
    Jump0,
    JumpNeg,
    EndSub,
    End,
    OutChar,
    OutNum,
    ReadChar,
    ReadNum,
};

struct Token {
    TokenType type;
    std::string val;
};

using TokenList = std::vector<Token>;

struct Parser {
    Parser() : index(0) {}

    TokenList parse(const std::string & _code) {
        code = _code;

        while (index < code.size()) {
            if (is_ws()) {
                advance();
                if (is_ws()) {
                    advance();
                    std::string num;
                    while (!is_lf()) {
                        num += peek();
                        advance();
                    }
                    add({TokenType::Push, num});
                } else if (is_lf() && is_ws(peek_next())) {
                    advance();
                    add({TokenType::Dup});
                } else if (is_lf() && is_tab(peek_next())) {
                    advance();
                    add({TokenType::Swap});
                } else if (is_lf() && is_lf(peek_next())) {
                    advance();
                    add({TokenType::Disc});
                }
            } else if (is_tab()) {
                advance();
                if (is_ws()) {
                    advance();
                    if (is_ws()) {
                        advance();
                        if (is_ws()) {
                            advance();
                            add({TokenType::Add});
                        } else if (is_tab()) {
                            advance();
                            add({TokenType::Sub});
                        } else if (is_lf()) {
                            advance();
                            add({TokenType::Mul});
                        }
                    } else if (is_lf()) {
                        advance();
                        if (is_ws()) {
                            advance();
                            add({TokenType::Div});
                        } else if (is_tab()) {
                            advance();
                            add({TokenType::Mod});
                        }
                    }
                } else if (is_tab()) {
                    advance();
                    if (is_ws()) {
                        advance();
                        add({TokenType::Store});
                    } else if (is_tab()) {
                        add({TokenType::Load});
                    }
                } else if (is_lf()) {
                    advance();
                    if (is_ws()) {
                        advance();
                        if (is_ws()) {
                            advance();
                            add({TokenType::OutChar});
                        } else if (is_tab()) {
                            advance();
                            add({TokenType::OutNum});
                        }
                    } else if (is_tab()) {
                        advance();
                        if (is_ws()) {
                            advance();
                            add({TokenType::ReadChar});
                        } else if (is_tab()) {
                            advance();
                            add({TokenType::ReadNum});
                        }
                    }
                }
            } else if (is_lf()) {
                advance();
                if (is_ws()) {
                    advance();
                    if (is_ws()) {
                        advance();
                        add({TokenType::Mark});
                    } else if (is_tab()) {
                        advance();
                        add({TokenType::Call});
                    } else if (is_lf()) {
                        advance();
                        add({TokenType::Jump});
                    }
                } else if (is_tab()) {
                    advance();
                    if (is_ws()) {
                        advance();
                        add({TokenType::Jump0});
                    } else if (is_tab()) {
                        advance();
                        add({TokenType::JumpNeg});
                    } else if (is_lf()) {
                        advance();
                        add({TokenType::EndSub});
                    }
                } else if (is_lf()) {
                    advance();
                    if (is_lf()) {
                        add({TokenType::End});
                    }
                }
            }
        }
    }

private:
    TokenList tokens;
    std::string code;
    std::size_t index;

    char peek() {return code[index];}
    char peek_next() {return code[index+1];}
    char advance(int d = 1) {index += d; return code[index];}

    void add(const Token & token) {
        tokens.push_back(token);
    }

    bool is_ws(char c = 0) {
        if (c != 0) {
            return c == ' ';
        }
        return peek() == ' ';
    }
    bool is_lf(char c = 0) {
        if (c != 0) {
            return c == '\n';
        }
        return peek() == '\n';
    }
    bool is_tab(char c = 0) {
        if (c != 0) {
            return c == '\t';
        }
        return peek() == '\t';
    }
};

// Runtime-level
struct Interpreter {
    Interpreter() : index(0) {}

    void interpret(const TokenList & _tokens) {
        tokens = _tokens;

        while (!end()) {
            switch (peek().type) {

            }
        }
    }

private:
    TokenList tokens;
    std::size_t index;

    Token peek() {return tokens[index];}
    Token peek_next() {return tokens[index+1];}
    Token advance(int d) {index += d; return tokens[index];}

    bool end() {
        return peek().type == TokenType::End;
    }
};

std::string whitespace(const std::string &code, const std::string &inp = std::string()) {
    std::map<int, int> heap;
    std::vector<int> stack;
    std::string output;

    // simple lexer
    TokenList tokens;
    for (const auto & c : code) {
        if (c == ' ') tokens.push_back(Token::Ws);
        else if (c == '\n') tokens.push_back(Token::Nl);
        else if (c == '\t') tokens.push_back(Token::Tab)
    }

    Parser parser;
    Tree tree = parser.parse(tokens);

    Interpreter ip;
    ip.interpret(tree);

    return output;
}
