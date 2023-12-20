#ifndef ICOMMAND_H
#define ICOMMAND_H

namespace s21 {

class ICommand {
 public:

  /// @brief интерфейс для реализации конструктора команды
  virtual ~ICommand() = default;

  /// @brief интерфейс для реализации выполнения команды
  virtual void execute() = 0;

  /// @brief интерфейс для реализации отмены команды
  virtual void undo() = 0;
};

}  // namespace s21

#endif  // ICOMMAND_H
