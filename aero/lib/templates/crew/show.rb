"
<table class = 'list'>
  <thead>
  <tbody>
    <tr>
      <th>Название:</th>
      <td>#{@item[:name]}</td>
    </tr>
    <tr>
      <th>Пилот:</th>
      <td>#{@item.pilot[:second_name]}</td>
    </tr>
    <tr>
      <th>Второй пилот:</th>
      <td>#{@item.second_pilot[:second_name]}</td>
    </tr>
    <tr>
      <th>Стюард:</th>
      <td>#{@item.stuard1[:second_name]}</td>
    </tr>
    <tr>
      <th>Второй стюард:</th>
      <td>#{@item.stuard2[:second_name]}</td>
    </tr>
    <tr>
      <th>Бортмеханик:</th>
      <td>#{@item.mechanic[:second_name]}</td>
    </tr>
    <tr>
      <th>Рейсы:</th>
      <td>
        #{
        @item.flights.map do |flight|
          "#{flight[:code]}<br>"
        end.join('\n')
        }
      </td>
    </tr>
    <tr>
      <th>Занят?</th>
      <td>#{@is_busy}</td>
    </tr>
    <tr>
      <th><a href = 'aero?controller=Crew&action=edit&id=#{@item[:id]}'>Редактировать</a></th>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Flight&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
