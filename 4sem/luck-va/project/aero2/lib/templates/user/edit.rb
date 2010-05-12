"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'User'>
<input type = 'hidden' name = 'action' value = 'edit'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'item[id]' value = '#{@item[:id]}'>
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Логин:</th>
      <td><input type = 'text' name = 'item[name]' value = '#{@item[:login]}'></td>
    </tr>
    <tr>
      <th>Пароль:</th>
      <td><input type = 'text' name = 'item[code]' value = '#{@item[:password]}'></td>
    </tr>
    <tr>
      <th>Информация:</th>
      <td><input type = 'text' name = 'item[description]' value = '#{@item[:info]}'></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=User&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
