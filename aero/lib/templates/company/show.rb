"
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Название авиакомпании:</th>
      <td>#{@item[:name]}</td>
    </tr>
    <tr>
      <th>Код:</th>
      <td>#{@item[:code]}</td>
    </tr>
    <tr>
      <th>Описание:</th>
      <td>#{@item[:description]}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Company&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
