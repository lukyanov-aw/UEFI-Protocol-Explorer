/** @file
 * Содержит описание типа EVENT_PROVIDER и набор операций над ним.
 * Объекты типа генерируют события, связанные с загрузкой системы.
 */
#include <Uefi.h>
#include <Library/LoadingEvent.h>
#include <Library/VectorLib.h>

#ifndef EVENT_PROVIDER_LIB_H_
#define EVENT_PROVIDER_LIB_H_

// -----------------------------------------------------------------------------
typedef
VOID
(*ADD_EVENT) (
  IN VOID           *ExternalData,  // Получаем извне и передаём без изменений.
  IN LOADING_EVENT  *Event          // Произошедшее событие.
  );

// -----------------------------------------------------------------------------
typedef struct
{
  // Зависит от реализации.
  VOID *Data;
  // Функция обратного вызова, вызывается при появлении нового события.
  ADD_EVENT AddEvent;
  // Данные для AddEvent, которые мы получаем извне.
  VOID *ExternalData;
} EVENT_PROVIDER;

// -----------------------------------------------------------------------------
/**
 * Инициализирует структуру EVENT_PROVIDER.
 * Функция должна быть обязательно однократно вызвана перед использованием объекта.
 *
 * @param This                      Указатель на структуру EVENT_PROVIDER, для которой выполняется инициализация.
 * @param AddEvent                  Функция обратного вызова, EVENT_PROVIDER вызывает её при поступлении новых событий.
 * @param ExternalData              Передаётся в AddEvent при каждом вызове.
 *
 * @retval EFI_SUCCESS              Операция завершена успешно.
 * @retval Любое другое значение    Произошла ошибка, объект не инициализирован.
 */
EFI_STATUS
EventProvider_Construct(
  IN OUT EVENT_PROVIDER  *This,
  IN     ADD_EVENT       AddEvent,
  IN     VOID            *ExternalData
  );

// -----------------------------------------------------------------------------
/**
 * Освобождает память из-под структуры.
 * Функция должна быть обязательно однократно вызвана после завершения использования объекта.
 */
VOID
EventProvider_Destruct (
  EVENT_PROVIDER *This
  );

// -----------------------------------------------------------------------------
/**
 * EVENT_PROVIDER коннектится к системе и начинает сбор событий.
 *
 * @retval EFI_SUCCESS              EVENT_PROVIDER успешно законнектился.
 * @retval Любое другое значение    Произошла ошибка, объект в том же состоянии что и до вызова функции.
 */
EFI_STATUS
EventProvider_Start (
  EVENT_PROVIDER *This
  );

// -----------------------------------------------------------------------------
/**
 * EVENT_PROVIDER отсоединяется от системы и прекращает сбор событий.
 */
VOID
EventProvider_Stop (
  EVENT_PROVIDER *This
  );

// -----------------------------------------------------------------------------

#endif // EVENT_PROVIDER_LIB_H_
