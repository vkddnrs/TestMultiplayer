# TestMultiplayer

Краткое описание по юзабилити.
В блюпринтах Лампочек устанавливается график Curve (лежат в папке Blueprints) , по которому они анимируются в цветах.В Блюпринте Плиты в массив Лампочек пипеткой можно 
набрать лампочки, которые, в свою очередь можно вытащить на уровень из папки Blueprints. 
Хотел сделатьу правление цветом материала лампочек чисто из кода, но почему-то не смог заставить объект Динамического материала работать - он меняет цвет тоько в бегин плее
и только один раз. Провозился с этим ооочень долго. В сети есть такие же как я, но похоже, в прошлых версиях движка они как-то частично решали проблему. Короче, пришлось через
блюпринты.
Таймлайн для лампочек сделал внутри самой лампочки - боялся с репликациями не смогу его настроить если будет он отдельным компонентом ( с репликациями тоже долго
возился в самом начале). Потом уже не хватило ни сил ни времени сделать его компонентом для плиты (с этим тоже пришлось бы эксперементировать - раньше компоненты в 
плюсах еще не делал - в основном я сидел на геймплее). Поэтому анимку плите набросал в блюпринтах.
Классы лампочек наследовал от базовой с переопределением метода, где прописано поведение смены цветов. Если что-то не упомянул - готов ответить устно.

Спасибо за внимание :-)

PS UE4.25.4
