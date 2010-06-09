"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'FlyPersonal'>
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
      <th>Должность:</th>
       <td>#{fly_personals_select('item[job_title]', "#{@item[:job_title]}")}</td>
      <th>
        <br>
        <div style = 'margin-left: 10px;'>фамилия:</div>
        <div style = 'margin-left: 10px;'>имя:</div>
        <div style = 'margin-left: 10px;'>отчество:</div>
      </th>
      <td>
        &nbsp;<br>
        <input type = 'text' name = 'item[first_name]' value = '#{@item[:first_name]}' size = '30'><br>
        <input type = 'text' name = 'item[second_name]' value = '#{@item[:second_name]}' size = '30'><br>
        <input type = 'text' name = 'item[patronymic_name]' value = '#{@item[:patronymic_name]}' size = '30'>
      </td>
      <th>Возраст:</th>
      <td><input type = 'text' name = 'item[age]' value = '#{@item[:age]}'></td>
      
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=FlyPersonal&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
