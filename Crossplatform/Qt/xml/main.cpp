#include <QtWidgets>
#include <QtXml>

QString content;

void traverseNode(const QDomNode& node) {
    QDomNode domNode = node.firstChild();
    while (not domNode.isNull()) {
        if (domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if (not domElement.isNull()) {
                content.append("<b>TagName:</b> ");
                content.append(domElement.tagName());
                content.append("<br>");
                auto attributes = domElement.attributes();
                for (int i = 0; i < attributes.length(); ++i) {
                    content.append("<b>Attribute:</b> ");
                    content.append("<i>Name:</i> ");
                    content.append(attributes.item(i).nodeName());
                    content.append(" <i>Value:</i> ");
                    content.append(attributes.item(i).nodeValue());
                    content.append("<br>");
                }
                content.append("<b>Text:</b> ");
                content.append(domElement.text());
                content.append("<br><br>");
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QDomDocument doc;
    QFile xmlFile(":/xml/ief.xml");
    if (xmlFile.open(QFile::ReadOnly)) {
        if (doc.setContent(&xmlFile)) {
            QDomElement element = doc.documentElement();
            traverseNode(element);
        }
        xmlFile.close();
    }
    QTextEdit text;
    text.setReadOnly(true);
    text.setHtml(content);
    text.show();

    return app.exec();
}
