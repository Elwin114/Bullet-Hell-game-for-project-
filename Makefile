# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -I"D:/raylib/raylib/raylib2/include"
LDFLAGS = -L"D:/raylib/raylib/raylib2/lib" -lraylib -lopengl32 -lgdi32 -lwinmm

# Целевой исполняемый файл
TARGET = game.exe

# Исходные файлы (все .cpp из папки src)
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию (сборка всего)
all: $(TARGET)

# Сборка исполняемого файла из объектных файлов
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Компиляция каждого .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Копирование ресурсов после сборки (опционально)
# Если используете динамическую библиотеку, скопируйте raylib.dll
copy_resources:
	@if exist "D:/raylib/raylib/raylib2/bin/raylib.dll" copy "D:/raylib/raylib/raylib2/bin/raylib.dll" .
	@if exist "assets" xcopy /E /I /Y assets assets

# Очистка (удаление объектных файлов и исполняемого)
clean:
	del /Q $(OBJS) $(TARGET) 2>nul || true

# Запуск игры
run: $(TARGET)
	$(TARGET)

# Удобная команда: собрать и скопировать ресурсы
build: $(TARGET) copy_resources

# Phony-цели (не являются файлами)
.PHONY: all clean run build copy_resources