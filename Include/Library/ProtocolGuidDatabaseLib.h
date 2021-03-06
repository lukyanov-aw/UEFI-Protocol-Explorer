/** @file
 * Библиотека для работы с БД известных протоколов.
 * Сама БД генерится скриптом.
 */
#include <Uefi.h>

#ifndef PROTOCOL_GUID_DATABASE_LIB_H_
#define PROTOCOL_GUID_DATABASE_LIB_H_

// -----------------------------------------------------------------------------
/**
 * Возвращает осмысленное имя протокола по его GUID'у.
 *
 * @param Guid                      Указатель на GUID протокола.
 *
 * @retval NULL                     Протокол не найден в БД.
 * @return Указатель на строку, содержащую имя протокола.
 *         Данная строка существует на протяжении всей жизни программы,
 *         перезаписывать её не следует.
 */
CHAR16 *
GetProtocolName (
  IN EFI_GUID *Guid
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает количество известных GUID.
 *
 * @retval Количество известных GUID.
 */
UINTN
GetProtocolGuidCount (
  );

// -----------------------------------------------------------------------------
/**
 * Возвращает указатель на GUID протокола с индексом Index.
 *
 * @param Index  Индекс протокола в БД.
 *
 * @retval NULL  Индекс выходит за пределы [0 .. GetProtocolGuidCount()]
 * @retval Указатель на GUID протокола с указанным индексом.
 */
EFI_GUID *
GetProtocolGuid (
  IN UINTN Index
  );

// -----------------------------------------------------------------------------

#endif // PROTOCOL_GUID_DATABASE_LIB_H_
