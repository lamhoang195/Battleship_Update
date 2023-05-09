
============================= BATTLESHIP =============================



### Giới Thiệu

Một trò chơi đơn giản được viết bằng C++ sử dụng SDL2 làm thư viện đồ họa. Đây là dự án làm game đầu tiên của tôi cho bài tập lớn môn Lập trình nâng cao. Tôi viết dự án của mình trên Window (64bit) bằng CodeBlocks IDE (64bit).


### Cách Chơi

Sau khi cài thư viện SDL xong bạn chỉ cần tải dự án của tôi rồi nhấn đúp vào `SDL_Lam_Game.cbp` để chạy trò chơi. Player dùng chuột di đến ô `Play` để chơi game hoặc `Exit` để thoát game. Player dùng chuột để di chuyển nhân vật và nhấn chuột phải hoặc chuột trái để bắn đạn. Vào game Player có 5 máu. Sẽ có 3 loại máy bay địch với máu khác nhau và hạ gục máy bay địch Player nhận được 1 điểm. Khi Player đạt đến 50 điểm thì sẽ có boss xuất hiện. Khi bị dính đạn địch Player sẽ có 3 giây được miễn thương. Player hạ gục Boss thành công sẽ sẽ Win còn nếu hết máu sẽ thua(Boss có 500 máu). Khi Win hoặc GameOver bạn nhấn `Exit` thoát game và chạy lại như lúc đầu.


### Cài Đặt

Để chạy chương trình và chơi game này, đầu tiên chúng ta cần tải và cài đặt CodeBlocks và thư viện SDL, SDL image, SDL mixer và SDL font.  
`Links`  
SDL2 : [https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2)  
SDL2 : [https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2)  
SDL_image: [https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.2](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.2)  
SDL_mixer: [https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3](https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)  
SDL_ttf: [https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2)  
Code::Blocks: http://www.codeblocks.org/downloads/binaries/  

Với thư viện SDL (1), sau khi tải về: Giải nén vào một thư mục nào đó, trong đó có 2 thư mục, chỉ dùng đến 01:

`○ i686-w64-mingw32 dành cho CodeBlock 32 bit. `  
`○ x86_64-w64-mingw32 dành cho CodeBlock 64 bit hoặc có compiler 64 bit.`  

Các bước cài SDL:

Copy file dll ...\x86_64-w64-mingw32\bin\SDL2.dll vào thư mục mã nguồn project (nơi có các file .cpp)  
Setting | Compiler | Linker Setting: chép vào Other Linker Option: -lmingw32 -lSDL2main -lSDL2  
Setting | Compiler | SearchDirectory | Compiler: thêm vào Policy đường dẫn: ...\x86_64-w64-mingw32\include\SDL2  
Setting | Compiler | SearchDirectory | Linker: thêm vào Policy đường dẫn: ...\x86_64-w64-mingw32\lib  
Cài thư viện image, ttf, mix các bạn cũng làm tương tự cài SDL.  

### REFERENCE SOURCES

`Lazy Foo' Productions` : https://lazyfoo.net/tutorials/SDL/index.php  
`Phát triển phần mềm 123` : https://phattrienphanmem123az.com/lap-trinh-game-cpp




