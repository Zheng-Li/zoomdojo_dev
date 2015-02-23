<div id="zd-tabs-add-form">
    <div class="bundle-type">
        <h3>Choose type:</h3>
        <div>
            <label>
                <input type="radio" name="bundle" data-bundle="node" value="0" class="bundle def-check" checked="checked" /><span>Node</span>
            </label>
            <label>
                <input type="radio" name="bundle" data-bundle="voc" value="0" class="bundle" /><span>Taxonomy</span>
            </label>
        </div>
    </div>
    <div class="clearfix"></div>
    <div class="show-children hide">
        <h3>Show-children:</h3>
        <div>
            <label>
                <input type="checkbox" name="children" value="0" id="children" checked="checked" /><span>Yes</span>
            </label>
        </div>
    </div>
    <div class="clearfix"></div>
    <div class="groups-list data-type-choose">
        <div class="content-types-list">
            <h3>Choose content type:</h3>
            <div class="line-block">
                <?php foreach ($contentTypes as $ct): ?>
                    <div class="item">
                        <input type="radio" name="contenttype" data-type="<?php print $ct->type; ?>" value="0" class="content-type" /><span><?php print $ct->name; ?></span>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
        <div class="taxonomy-terms-list hide">
            <h3>Choose vocabulary:</h3>
            <div class="line-block">
                <?php foreach ($vocabularies as $voc): ?>
                    <div class="item">
                        <input type="radio" name="vocabulary" data-type="<?php print $voc->vid; ?>" value="0" class="content-type" /><span><?php print $voc->name; ?></span>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
    </div>
    <div class="clearfix"></div>
    <div class="select-entity hide">
        <h3>Choose entity:</h3>
        <div>
            <select id="entity"></select>
            <a id="view-choose-page" class="button">View page</a>
            <a id="view-block-field" class="button">Select page</a>
        </div>
    </div>
    <div class="clearfix"></div>
    <div class="tab-item-form hide"></div>
</div>
<script type="text/x-html" id="option-template">
    <option data-url="<%= url %>" data-lang="<%= language %>" value="<%= id %>"><%= title %> (<%= language %>) [<%= id %>]</option>    
</script>