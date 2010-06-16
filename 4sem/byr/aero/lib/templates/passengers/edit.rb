"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Passengers'>
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
      <th>Фамилия</th>
      <td><input type = 'text' name = 'item[surname]' value = '#{@item[:surname]}'></td>
    </tr>
    <tr>
      <th>Имя</th>
      <td><input type = 'text' name = 'item[name]' value = '#{@item[:name]}'></td>
    </tr>
    <tr>
      <th>Отчество</th>
      <td><input type = 'text' name = 'item[patronymic]' value = '#{@item[:patronymic]}'></td>
    </tr>
<th>Паспорт</th>
      <td><input type = 'text' name = 'item[npass_i]' value = '#{@item[:npass_i]}'></td>
    </tr>
<th> Загран Паспорт</th>
      <td><input type = 'text' name = 'item[npass_e]' value = '#{@item[:npass_e]}'></td>
    </tr>
      <tr>
   
        <th>Доп. информация:</th>
      <td><textarea name = 'item[info]'>#{@item[:info]}</textarea></td>

    <tr>
      <th>Рейс:</th>
      <td>#{flights_select('item[flight_id]', "#{@item[:flight_id]}")}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Flights&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
