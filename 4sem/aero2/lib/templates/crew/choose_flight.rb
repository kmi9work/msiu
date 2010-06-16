"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'Crew'>
<input type = 'hidden' name = 'action' value = 'set_flight'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<input type = 'hidden' name = 'id' value = '#{@id}'>
<tbody>

<tr>
  <th>Рейс:</th>
  <td>#{flight_select('item[flight_id]', @selected)}</td>
</tr>

</tbody>
<tfoot>
  <tr>
    <th colspan = '2'>
      <input type = 'submit' value = 'Внести изменения'>
      <input type = 'button' value = 'Назад к списку'
             onclick = 'javascript:document.location=\"aero.rb?controller=Crew&action=list\"'>
</th>
  </tr>
</tfoot>
</table>
</form>
"