"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Crew'>
<input type = 'hidden' name = 'action' value = 'edit'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'flight_id' value = '#{@cgi.params['flight_id'][0]}'>
<input type = 'hidden' name = 'item[id]' value = '#{@item[:id]}'>
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Пилот:</th>
      <td>#{job_select('item[pilot_id]', 0)}</td>
    </tr>
    <tr>
      <th>Стюард:</th>
      <td>#{job_select('item[stuard1_id]', 1)}</td>
    </tr>
    <tr>
      <th>Второй Стюард:</th>
      <td>#{job_select('item[stuard2_id]', 1)}</td>
    </tr>
    <tr>
      <th>Бортмеханик:</th>
      <td>#{job_select('item[mechanic_id]', 2)}</td>
    </tr>
    <tr>
      <th>Второй пилот:</th>
      <td>#{job_select('item[second_pilot_id]', 3)}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Flight&action=list\"'>
 </th>
    </tr>
  </tfoot>
</table>
"
                       
