import QtQuick
import QtQuick.Controls
import TextAnalyse
import Main

Item {
    id: container
    anchors.fill: parent
    Row {
        id: main_frame
        Column {
            id: translate_input
            height: parent.height
            width: parent.width / 2
            Row {
                id: setting_area
                spacing: 5
                ComboBox {
                    id: src_language
                    editable: false
                    width: 100
                    height: 30
                    textRole: "key"
                    model: ListModel {
                        id: src_model
                        ListElement {
                            key: "中文"
                            value: "cmn"
                        }
                        ListElement {
                            key: "英文"
                            value: "eng"
                        }
                    }
                }
                Button {
                    id: switch_language
                    width: 50
                    height: 20
                    text: "~"
                    font.pixelSize: 20
                    onClicked: {
                        var tempvar = tar_language.currentIndex
                        tar_language.currentIndex = src_language.currentIndex
                        src_language.currentIndex = tempvar
                    }
                }
                ComboBox {
                    id: tar_language
                    editable: false
                    width: 100
                    height: 30
                    textRole: "key"
                    currentIndex: 1
                    model: ListModel {
                        id: tar_model
                        ListElement {
                            key: "中文"
                            value: "cmn"
                        }
                        ListElement {
                            key: "英文"
                            value: "eng"
                        }
                    }
                }
                Button {
                    id: history_record_button
                    width: 100
                    height: 30
                    text: "历史记录"
                }
            }
            ScrollView {
                id: src_input_text
                height: 550
                width: 360
                TextArea {
                    id: translate_text
                    anchors.fill: parent
                    placeholderText: qsTr("输入需要翻译的内容...")
                    wrapMode: Text.WordWrap
                    font.pixelSize: 20
                }
            }
            Row {
                id: finish_area
                height: 50
                Button {
                    id: clear_button
                    text: "清空"
                    width: 70
                    height: 40
                }
                Button {
                    id: translate_button
                    text: "翻译"
                    width: 70
                    height: 40
                    focus: true
                }
            }
        }
        Column {
            id: translate_output
            y: src_input_text.y
            ScrollView {
                id: tar_output_text
                height: 550
                width: 360
                TextArea {
                    id: output_text
                    anchors.fill: parent
                    wrapMode: Text.WordWrap
                    readOnly: true
                    font.pixelSize: 20
                }
            }
        }
    }
    TextAnalyse {
        id: text_analyse
    }
    Keys.onReturnPressed: {
        translate_button.clicked()
    }

    Connections {
        target: clear_button
        onClicked: {
            translate_text.text = ""
        }
    }
    Connections {
        target: translate_button
        onClicked: {
            var src_text = translate_text.text
            var model_name = "t2tt"
            var current_index_src = src_language.currentIndex
            var current_index_tar = tar_language.currentIndex
            var src_language_input = src_model.get(current_index_src).value
            var tar_language_input = tar_model.get(current_index_tar).value
            console.log(tar_language_input)
            text_analyse.PostSrcText(src_text, model_name, tar_language_input,
                                     src_language_input)
        }
    }
    Connections {
        target: text_analyse
        onSignals_ProcessedText: translate_result => {
                                     output_text.text = translate_result
                                 }
    }

    Connections {
        target: history_record_button
        onClicked: {
            text_analyse.OpenDialog()
        }
    }
}
