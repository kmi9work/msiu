"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Terminal'>
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
      <th>Название:</th>
      <td><input type = 'text' name = 'item[name]' value = '#{@item[:name]}'></td>
    </tr>
    <tr>
      <th>Описание:</th>
      <td><input type = 'text' name = 'item[description]' value = '#{@item[:description]}'></td>
    </tr>
    <tr>
      <th>Нужен ли автобус?</th>
      <td>
        <select name = 'item[needs_bus]'>
          <option value = '#{true}' selected>да</option>
          <option value = '#{false}' selected>нет</option>
        </select>
      </td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=CheckInDesk&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"