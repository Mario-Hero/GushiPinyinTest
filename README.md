# 初中古诗文默写和拼音自测软件

这是一个用Qt制作的供学生做初中古诗文默写和拼音自测的软件。

我爸是初中语文老师，他希望能做一个给学生自测古诗文默写和拼音的软件，但他不会写代码。所以他负责把古诗文和拼音整理成对应的格式，我负责写软件读取和显示内容。

软件效果不错，也很实用。我爸已经用它来进行随堂测试许多回了。

## 软件截图

<img src="https://raw.githubusercontent.com/Mario-Hero/GushiPinyinTest/main/Screenshot/gushi.jpg" alt="gushi" style="zoom:33%;" />

<img src="https://github.com/Mario-Hero/GushiPinyinTest/blob/main/Screenshot/pinyin.jpg" alt="pinyin" style="zoom:33%;" />

## 下载地址

Windows 64位：

[古诗测试](https://github.com/Mario-Hero/GushiPinyinTest/releases/download/Main/Gushi.exe)

[拼音测试](https://github.com/Mario-Hero/GushiPinyinTest/releases/download/Main/Pinyin.exe)

## 使用说明

下载后直接打开即可（软件为64位，需要在64位电脑上打开，目前大多数电脑都是64位）。

### 古诗测试：

勾选年级，再点击生成所选题目，即可给出对应年级的随机古诗词。

点击生成全部题目，可给出所有年级的随机古诗词。

点击名句，给出名句。

点击看答案浏览答案，再点击该按钮隐藏答案。

点击计时开始来计时，点击计时重置来结束。

### 拼音测试：

这个测试是按顺序进行测试的。第一次打开程序，会生成随机的拼音列表，以后就按照这个列表进行测试，全部测试完会生成新的随机列表。

点击下一套题来继续做题。

勾选拼音前的框框来标记错题，以后点击复习错题时会显示这些题目，但你必须点击下一套题，这些错题才会保存到错题集。取消勾选框框来取消标记错题。

点击看答案浏览答案，再点击该按钮隐藏答案。

点击计时开始来计时，点击计时重置来结束。

## 欢迎打赏，感谢支持

<img src="https://files-cdn.cnblogs.com/files/mariocanfly/wechat.bmp" style="zoom:50%;" />

<br>

## 关于源代码

后文是关于源码的部分，如果你只是使用这个软件，就不用看后文了。

## 依赖

Qt 5

(即使安装了对Qt5的兼容，Qt 6仍然无法编译通过)

## 文本材料

### 古诗测试：

古诗测试的文本都在GushiTest\files里，7a表示七年级上册，7b表示七年级下册，mj110q.txt是名句的问题，mj110ans.txt是名句的答案。

txt文件里，每个古诗之间空一行，第一行是标题，第二行是作者，其中【】里的是朝代，《》表示出自某部作品。

### 拼音测试：

拼音测试的文本在PinyinTest\files\pinyin.txt，其中每个拼音后面可能有标记，比如“腌(ā)2臜(za)2”标记了2。拼音后不标记是只考字怎么写，标记1是考拼音，标记2是字和拼音随机选一个考。

第一次运行程序后，会生成pinyinRank.txt，这是打乱了的拼音列表。程序也会生成pinyinError.txt，这个文件第一行记录了当前复习到了列表的第几页，后面则是错题。

## License

The project is released under GNU Lesser General Public License.
