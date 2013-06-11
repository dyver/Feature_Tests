#include <string>

namespace tmsg
{
    /// Интерфейс журнала текстовых сообщений
    class TextMessageJournal
    {
        public :
            /// Положить текстовое сообщение в хранилище
            /// @param message: текстовое сообщение
            void put(TextMessage::Message *message);
            /// Получить из хранилища последнее текстовое сообщение
            /// @param message: текстовое сообщение
            void getLast(TextMessage::Message &message);
            /// Получить из хранилища текстовое сообщение по индексу
            /// @param index: индекс
            /// @param message: текстовое сообщение
            void getByIndex(int index, TextMessage::Message &message);
            /// Удалить из хранилища текстовое сообщение по индексу
            /// @param index: индекс
            void delByIndex(int index);
            /// Удалить из хранилища все текстовые сообщения
            void delAll();
            /// Получить из хранилища количество текстовых сообщений
            /// @return количество текстовых сообщений
            int getTotal();
    };
}
