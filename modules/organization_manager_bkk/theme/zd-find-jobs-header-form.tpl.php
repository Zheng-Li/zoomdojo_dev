<div class="front-top-block">
    <div class="front-tb-left">Quick Search for Jobs</div>
    <div class="front-tb-right">
        <form id="findJobsFormMini" action="/find-positions" method="get">
            <div class="row-fluid">
                <input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type employer name" class="fullwidth employer-autocomplete"/>
                <input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type location" />
            </div>
        </form>
        <a class="btn btn-danger btn-small fr-search-btn" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Go</a>
    </div>
</div>