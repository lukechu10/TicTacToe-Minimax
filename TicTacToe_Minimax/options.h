struct Option {
    char computer = 'x';
    char opponent = 'o';
    char empty = '_';
    
    Option() {}
    Option(const char& computer, const char& opponent, const char& empty) {
        this->computer = computer;
        this->opponent = opponent;
        this->empty = empty;
    }
    
    Option(const Napi::Object& options) {
        if (options.Has("computer")) {
            if (options["computer"].IsString()) {
                this->computer = options.Get("computer").ToString().Utf8Value()[0];
            }
        }
        if (options.Has("opponent")) {
            if (options["opponent"].IsString()) {
                this->opponent = options.Get("opponent").ToString().Utf8Value()[0];
            }
        }
        if (options.Has("empty")) {
            if (options["empty"].IsString()) {
                this->empty = options.Get("empty").ToString().Utf8Value()[0];
            }
        }
    }
};