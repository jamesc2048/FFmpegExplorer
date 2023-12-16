import os
from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtQml import *
from PySide2.QtWebEngine import *

class ViewModel(QObject):
    def default_property(type, name, initial_value):
        val = initial_value

        @Signal
        def notify_func(self):
            pass

        def read_func(self):
            return val

        def write_func(self, v):
            val = v
            notify_func.emit()

        return Property(str, read_func, write_func, notify=notify_func)

    def read_title(self):
        return self._title

    def write_title(self, val):
        self._title = val
        self.notify_title.emit()

    @Signal
    def notify_title(self):
        pass

    title = default_property(str, "title", "aaaaa") #Property(str, read_title, write_title, notify=notify_title)

    def __init__(self):
        super().__init__()
        self._title = "wowowowzzz"

def main():
    app = QGuiApplication([])
    QtWebEngine.initialize()
    engine = QQmlApplicationEngine()
    qml_file_path = os.path.join(os.path.dirname(__file__), 'main.qml')
    qml_url = QUrl.fromLocalFile(os.path.abspath(qml_file_path))

    vm = ViewModel()
    engine.rootContext().setContextProperty("viewModel", vm)

    engine.load(qml_url)
    app.exec_()

if __name__ == '__main__':
    main()
