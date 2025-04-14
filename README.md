# Text-to-Graphics-parser

Программа для перевода текстового описания в графический интерфейс. Пример файла содержится [здесь](https://github.com/AlbionVisual/Text-to-Graphics-parser-SFML-2021-School-project/blob/main/GraphicLayouts/layout.txt). Эту программу я делал будучи в 9-ом классе в 2021 году.

## Как выглядит

Простой интерфейс появится после запуска программы и чтения файла. Вот пример:

![Пример интерфейса, созданного программой](https://github.com/AlbionVisual/Text-to-Graphics-parser-SFML-2021-School-project/blob/main/clips/main-window.png)

## Синтаксис

В текстовый файл нужно вводить элементы в таком стиле:

```
layout
	settings
        window_height 900
		window_weight 1600
		antialiasing 5
		background 255 255 255
		name Layout
    /settings
    window
        circle
			name checkButton1
			x 100
			y 100
			radius 10
			color 200 200 200
		/circle

        button
			x 200
			y 140
			sizeX 90
			sizeY 20
			string But2
			name button2
			color 200 200 200
			thickness 1
			thickness_color 0 0 0
		/button
	/window
/layout
```

Также уже работают такие графические примитивы, как text, convex, input, button, rectangle и circle.
