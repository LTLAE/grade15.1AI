import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QCheckBox, QLabel, QGridLayout


class CheckBoxWindow(QWidget):
    have_milk = False
    have_hair = False
    have_feather = False
    fly_and_lay_eggs = False
    have_claws_and_canine_teeth_and_eyes_in_front = False
    eat_meat = False
    have_hoof = False
    ruminate_food = False
    yellow_brown = False
    have_black_stripes = False
    have_black_spots = False
    have_long_legs_and_long_neck = False
    dark_spots = False
    white = False
    can_fly = False
    can_not_fly = False
    black_and_white = False
    can_swim = False
    not_afraid_of_wind_and_waves = False

    mammal = False
    bird = False
    carnivore = False
    ungulate = False  # 有蹄动物
    even_toed = False  # 偶蹄动物

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):

        layout = QGridLayout()

        # create title
        self.title = QLabel('请选择动物特征')
        self.result = QLabel('正在分类中...')

        # create checkboxes
        self.checkboxes = [
            QCheckBox('有奶', self),
            QCheckBox('有毛发', self),
            QCheckBox('有羽毛', self),
            QCheckBox('会飞且下蛋', self),
            QCheckBox('有爪且有犬齿且目盯前方', self),
            QCheckBox('吃肉', self),
            QCheckBox('有蹄', self),
            QCheckBox('反刍食物', self),
            QCheckBox('黄褐色', self),
            QCheckBox('有黑色条纹', self),
            QCheckBox('有黑色斑点', self),
            QCheckBox('有长腿且长脖子', self),
            QCheckBox('有暗斑点', self),
            QCheckBox('白色', self),
            QCheckBox('会飞', self),
            QCheckBox('不会飞', self),
            QCheckBox('黑白色', self),
            QCheckBox('会游泳', self),
            QCheckBox('不怕风浪', self)
        ]

        for checkbox in self.checkboxes:
            checkbox.stateChanged.connect(self.on_checkbox_state_changed)

        # add title to layout
        layout.addWidget(self.title, 0, 0, 1, 3)

        # add checkboxes to layout
        for i, checkbox in enumerate(self.checkboxes):
            row = (i // 3) + 1
            col = i % 3
            layout.addWidget(checkbox, row, col)

        # add result to layout
        layout.addWidget(self.result, row + 1, 0, 1, 3)

        self.setLayout(layout)
        self.setWindowTitle('动物分类系统')
        self.show()

    def on_checkbox_state_changed(self, state):
        # if any checkbox changed, call this function
        sender = self.sender()
        if sender.text() == '有奶':
            self.have_milk = state == 2
        elif sender.text() == '有毛发':
            self.have_hair = state == 2
        elif sender.text() == '有羽毛':
            self.have_feather = state == 2
        elif sender.text() == '会飞且下蛋':
            self.fly_and_lay_eggs = state == 2
        elif sender.text() == '有爪且有犬齿且目盯前方':
            self.have_claws_and_canine_teeth_and_eyes_in_front = state == 2
        elif sender.text() == '吃肉':
            self.eat_meat = state == 2
        elif sender.text() == '有蹄':
            self.have_hoof = state == 2
        elif sender.text() == '反刍食物':
            self.ruminate_food = state == 2
        elif sender.text() == '黄褐色':
            self.yellow_brown = state == 2
        elif sender.text() == '有黑色条纹':
            self.have_black_stripes = state == 2
        elif sender.text() == '有黑色斑点':
            self.have_black_spots = state == 2
        elif sender.text() == '有长腿且长脖子':
            self.have_long_legs_and_long_neck = state == 2
        elif sender.text() == '有暗斑点':
            self.dark_spots = state == 2
        elif sender.text() == '白色':
            self.white = state == 2
        elif sender.text() == '会飞':
            self.can_fly = state == 2
        elif sender.text() == '不会飞':
            self.can_not_fly = state == 2
        elif sender.text() == '黑白色':
            self.black_and_white = state == 2
        elif sender.text() == '会游泳':
            self.can_swim = state == 2
        elif sender.text() == '不怕风浪':
            self.not_afraid_of_wind_and_waves = state == 2

        self.classify()

    def classify(self):
        # init result
        self.mammal = False
        self.bird = False
        self.carnivore = False
        self.ungulate = False  # 有蹄动物
        self.even_toed = False  # 偶蹄动物
        result_text = '正在分类中...'

        if self.have_milk:
            self.mammal = True
            result_text = '正在分类中... 此动物是哺乳动物'
        if self.have_hair:
            self.mammal = True
            result_text = '正在分类中... 此动物是哺乳动物'
        if self.have_feather:
            self.bird = True
            result_text = '正在分类中... 此动物是鸟类'
        if self.fly_and_lay_eggs:
            self.bird = True
            result_text = '正在分类中... 此动物是鸟类'
        if self.mammal and self.have_claws_and_canine_teeth_and_eyes_in_front:
            self.carnivore = True
            result_text = '正在分类中... 此动物是食肉动物'
        if self.mammal and self.eat_meat:
            self.carnivore = True
            result_text = '正在分类中... 此动物是食肉动物'
        if self.mammal and self.have_hoof:
            self.ungulate = True
            result_text = '正在分类中... 此动物是有蹄动物'
        if self.have_hoof and self.ruminate_food:
            self.even_toed = True
            result_text = '正在分类中... 此动物是偶蹄动物'

        if self.carnivore and self.yellow_brown and self.have_black_stripes:
            result_text = '此动物是老虎'
        elif self.carnivore and self.yellow_brown and self.have_black_spots:
            result_text = '此动物是金钱豹'
        elif self.carnivore and self.have_long_legs_and_long_neck and self.dark_spots:
            result_text = '此动物是长颈鹿'
        elif self.ungulate and self.white and self.have_black_stripes:
            result_text = '此动物是斑马'
        elif self.bird and self.can_not_fly and self.have_long_legs_and_long_neck and self.black_and_white:
            result_text = '此动物是鸵鸟'
        elif self.bird and self.can_not_fly and self.can_swim and self.black_and_white:
            result_text = '此动物是企鹅'
        elif self.bird and self.can_fly and self.not_afraid_of_wind_and_waves:
            result_text = '此动物是海燕'

        self.result.setText(result_text)
        self.result.repaint()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = CheckBoxWindow()
    sys.exit(app.exec_())
