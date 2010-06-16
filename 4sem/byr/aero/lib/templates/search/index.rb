"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Search'>
<input type = 'hidden' name = 'action' value = 'index'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<table class = 'list'>
  <caption>
    Поиск<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Имя:</th>
      <td><input type = 'text' name = 'item[name]' value = ''></td>
    </tr> 
    <tr>
      <th>Фамилия:</th>
      <td><input type = 'text' name = 'item[surname]' value = ''></td>
    </tr> 
    <tr>
      <th>Отчество:</th>
      <td><input type = 'text' name = 'item[patronymic]' value = ''></td>
    </tr> 
    <tr>
      <th>Номер паспорта:</th>
      <td><input type = 'text' name = 'item[npass_i]' value = ''></td>
    </tr> 
    <tr>
      <th>Номер загран паспорта:</th>
      <td><input type = 'text' name = 'item[npass_e]' value = ''></td>
    </tr> 
    <tr>
      <th>Рейс:</th>
      <td><input type = 'text' name = 'item[code]' value = ''></td>
    </tr> 
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Search&action=find\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
