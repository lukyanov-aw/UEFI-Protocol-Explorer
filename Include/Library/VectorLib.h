/** @file
 * Содержит описание типа VECTOR и набор операций над ним.
 */
#include <Uefi.h>

#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

// -----------------------------------------------------------------------------
/**
 * Простой динамический массив, по поведению схож с std::vector.
 * Для выделения и освобождения памяти испульзует сервисы EFI_BOOT_SERVICES.
 */
typedef struct
{
  UINTN CountAllocated;     // Количество выделенной памяти, измеряемое в элементах.
  UINTN CountUsed;          // Количество реально хранимых элементов.
  UINTN ObjectSize;         // Размер одного элемента в байтах.
  VOID  *AllocatedMemory;   // Указатель на выделенную память.
} VECTOR;

// -----------------------------------------------------------------------------
/**
 * Инициализирует структуру VECTOR, выделяет память под InitialCount элементов размера SizeOfElement.
 * Функция должна быть обязательно однократно вызвана перед использованием объекта.
 *
 * @param This                      Указатель на инициализируемую структуру вектора.
 * @param SizeOfElement             Размер одного элемента в байтах.
 * @param InitialCount              Начальный размер массива, измеряется в элементах (не байтах).
 *
 * @retval EFI_SUCCESS              Операция завершена успешно, массивом можно пользоваться.
 * @retval EFI_OUT_OF_RESOURCES     Не удалось выделить память.
 * @retval EFI_INVALID_PARAMETER    Один из параметров равен нулю.
 */
EFI_STATUS
Vector_Construct (
  IN OUT  VECTOR          *This,
  IN      UINTN           SizeOfElement,
  IN      UINTN           InitialCount
  );

// -----------------------------------------------------------------------------
/**
 * Освобождает память из-под структуры.
 * Функция должна быть обязательно однократно вызвана после завершения использования объекта.
 *
 * @param This                      Указатель на структуру вектора.
 */
VOID
Vector_Destruct (
  IN OUT  VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Добавляет копию объекта в конец вектора.
 *
 * @param This                      Указатель на структуру вектора.
 * @param Object                    Указатель на элемент, который требуется добавить.
 *
 * @retval EFI_SUCCESS              Операция завершена успешно.
 * @retval EFI_OUT_OF_RESOURCES     Не удалось выделить память.
 * @retval EFI_INVALID_PARAMETER    Один из параметров равен NULL.
 */
EFI_STATUS
Vector_PushBack (
  IN OUT  VECTOR          *This,
  IN      VOID            *Object
  );

// -----------------------------------------------------------------------------
/**
 * Удаляет объект с конца вектора и возвращает значение удалённого элемента,
 * но не освобождает выделенной памяти.
 *
 * @param This                      Указатель на структуру вектора.
 *
 * @retval NULL                     Вектор пуст, либо This == NULL.
 * @return Указатель на удалённое из вектора значение.
 *         При первом же добавлении элемента в вектор это значение будет утеряно.
 */
VOID *
Vector_PopBack (
  IN OUT  VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает указатель на элемент вектора с индексом Index.
 *
 * @param This                      Указатель на структуру вектора.
 * @param Index                     Индекс элемента в векторе, нумерация начинается с 0.
 *
 * @retval NULL                     Выход за границы вектора, либо This == NULL.
 * @return Указатель на элемент с индексом Index.
 */
VOID *
Vector_Get (
  IN      VECTOR          *This,
  IN      UINTN           Index
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает указатель на первый элемент вектора.
 *
 * @param This                      Указатель на структуру вектора.
 *
 * @retval NULL                     Вектор пуст, либо This == NULL.
 * @return Указатель на первый элемент вектора.
 */
VOID *
Vector_GetBegin (
  IN      VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает указатель на элемент вектора, следующий за последним.
 *
 * @param This                      Указатель на структуру вектора.
 *
 * @retval NULL                     Вектор пуст, либо This == NULL.
 * @return Указатель на элемент вектора, следующий за последним.
 */
VOID *
Vector_GetEnd (
  IN      VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает указатель на последний элемент вектора.
 *
 * @param This                      Указатель на структуру вектора.
 *
 * @retval NULL                     Вектор пуст, либо This == NULL.
 * @return Указатель на последний элемент вектора.
 */
VOID *
Vector_GetLast (
  IN      VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает количество хранимых элементов в векторе.
 *
 * @param This                      Указатель на структуру вектора.
 *
 * @return Количество хранимых элементов.
 */
UINTN
Vector_Size (
  IN      VECTOR          *This
  );

// -----------------------------------------------------------------------------
/**
 * Сбрасывает число занятых элементов до нуля, но не освобождает память.
 *
 * @param This                      Указатель на структуру вектора.
 */
VOID
Vector_Clear (
  IN OUT  VECTOR          *This
  );


// -----------------------------------------------------------------------------
/**
 * Пример цикла по всем элементам вектора:
 *
 *   VECTOR MyVector;
 *   Vector_Construct (&MyVector, sizeof(MY_TYPE),  1024);
 *
 *   // ...
 *
 *   FOR_EACH_VCT(MY_TYPE, PointerToElement, MyVector) {
 *     // Тут можно использовать PointerToElement,
 *     // он указывает на текущий элемент вектора.
 *     *PointerToElement = ...;
 *   }
 *
 *   // ...
 *
 *   Vector_Destruct (&MyVector);
 */
#define FOR_EACH_VCT(ElementType, IteratorVarName, VectorName) \
  ElementType *IteratorVarName = Vector_GetBegin(&(VectorName)); \
  ElementType *EndIterator     = Vector_GetEnd(&(VectorName)); \
  for (; IteratorVarName != EndIterator; ++IteratorVarName)

#endif // VECTOR_LIB_H_